#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
volatile int count = 0;
volatile int global = 0;
int cycles = 0;

int try(volatile int *mutex)
{
    return __sync_val_compare_and_swap(mutex, 0, 1);
}

void lock(volatile int *mutex)
{
    int i = 0;
    while (try(mutex) != 0)
    {
        if (i == 0)
            cycles++;
        i++;
        sched_yield();
    }

    if(i>0)
        printf("amount of iteration while in lock is %d\n", i);
}
void unlock(volatile int *mutex)
{
    *mutex = 0;
}

typedef struct args
{
    int inc;
    int id;
    volatile int *mutex;
} args;

void *increment(void *arg)
{
    int inc = ((args *)arg)->inc;
    int id = ((args *)arg)->id;
    volatile int *mutex = ((args *)arg)->mutex;
    for (int i = 0; i < inc; i++)
    {
        lock(mutex);
        count++;
        unlock(mutex);
    }
}

int main(int argc, char *argv[])
{
    printf("Lebedev 37 \n");

    if (argc != 2)
    {
        printf("usage peterson <inc>\n");
        exit(0);
    }
    int inc = atoi(argv[1]);
    pthread_t one_p, two_p;
    args one_args, two_args;
    one_args.inc = inc;
    two_args.inc = inc;
    one_args.id = 0;
    two_args.id = 1;
    one_args.mutex = &global;
    two_args.mutex = &global;
    pthread_create(&one_p, NULL, increment, &one_args);
    pthread_create(&two_p, NULL, increment, &two_args);
    pthread_join(one_p, NULL);
    pthread_join(two_p, NULL);
    printf("result is %d \n", count);
    return 0;
}