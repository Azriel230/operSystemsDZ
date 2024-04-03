#include "csapp.h"
#include "csapp.c"

void initjobs()
{
}

void addjob(int pid)
{
}

void deletejob(int pid)
{
}

/* $begin procmask2 */
void handler(int sig)
{
    int olderrno = errno;
    sigset_t mask_all, prev_all;
    pid_t pid;

    Sigfillset(&mask_all);
    while ((pid = waitpid(-1, NULL, 0)) > 0) { /* Reap a zombie child */
        Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
        deletejob(pid); /* Delete the child from the job list */
        Sigprocmask(SIG_SETMASK, &prev_all, NULL);
    }
    if (errno != ECHILD)
        Sio_error("waitpid error");
    errno = olderrno;
}
    
int main(int argc, char **argv)
{
    printf("Lebedev 37\n");

    int pid;
    sigset_t mask_all, mask_one, prev_one;

    Sigfillset(&mask_all); // mask_all содержит все сигналы
    Sigemptyset(&mask_one); //mask_one инициализирована и пустая
    Sigaddset(&mask_one, SIGCHLD); // в mask_one добавили SIGCHILD
    Signal(SIGCHLD, handler);
    initjobs(); /* Initialize the job list */

    while (1) {
        Sigprocmask(SIG_BLOCK, &mask_one, &prev_one); //родителю заблокировали SIGCHILD
        if ((pid = Fork()) == 0) { /* Child process */
            Sigprocmask(SIG_SETMASK, &prev_one, NULL); // у ребенка заблокирован SIGCHILD по наследству, вернули обычную маску
            Execve("/bin/date", argv, NULL);
        }
        Sigprocmask(SIG_BLOCK, &mask_all, NULL); // родителю заблокировали все сигналы
        addjob(pid);  /* Add the child to the job list */
        Sigprocmask(SIG_SETMASK, &prev_one, NULL);  /* родителю разблокировали всё*/
    }
    exit(0);
}