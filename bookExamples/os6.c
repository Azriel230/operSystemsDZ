#include "csapp.h"
#include "csapp.c"


void handler1(int sig)
{
    int olderrno = errno;

    while(waitpid(-1, NULL, WNOHANG) > 0){
        Sio_puts("Handler reaped child\n");
    }
    if (errno != ECHILD)
        Sio_error("waitpid error");
    Sleep(1);
    errno = olderrno;
}

int main()
{
    printf("Lebedev 37\n");
    int i, n;
    char buf[MAXBUF];

    if (signal(SIGCHLD, handler1) == SIG_ERR)
        unix_error("signal error");

    /* Родитель запускает дочерние процессы */
    for (i = 0; i < 3; i++) {
        if (Fork() == 0) {
            printf("Hello from child %d\n", (int)getpid());
            exit(0);
        }
    }

    /* Родитель ждет ввода с терминала и обрабатывает его */
    if ((n = read(STDIN_FILENO, buf, sizeof(buf))) < 0)
        unix_error("read");

    printf("Parent processing input\n");
    while (1)
        ;

    exit(0);
}