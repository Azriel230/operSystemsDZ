#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Lebedev 37\n");
    pid_t pid;
    /* Дочерний процесс приостанавливается до получения сигнала SIGKILL,
    после чего завершается */
    if ((pid = fork()) == 0) {
        pause(); /* Ждать доставки сигнала */
        printf("control should never reach here!\n");
        exit(0);
    }

    /* Родитель посылает сигнал SIGKILL потомку */
    kill(pid, SIGKILL);
    exit(0);
 }
