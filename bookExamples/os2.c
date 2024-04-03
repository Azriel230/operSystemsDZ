#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void unix_error(const char *msg)
{
    int errnum = errno;
    fprintf(stderr, "%s (%d: %s)\n", msg, errnum, strerror(errnum));
    exit(EXIT_FAILURE);
}

void sigint_handler(int sig) /* обработчик SIGINT */
{
    printf("Caught SIGINT!\n");
    exit(0);
}
int main()
{
    printf("Lebedev 37\n");
    /* Установить обработчик сигнала SIGINT */
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
        unix_error("signal error");

    pause(); /* Ждать получения сигнала */

    return 0;
}