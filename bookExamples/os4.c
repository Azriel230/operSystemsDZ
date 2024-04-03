#include "csapp.h"
#include "csapp.c"

void sigint_handler(int sig) 
{
    Sio_puts("Caught SIGINT in safe handler!\n"); 
    _exit(0); 
}

int main()
{
    printf("Lebedev 37\n");
    
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");

    pause();

    return 0;
}