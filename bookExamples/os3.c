#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(){    
    printf("Lebedev 37\n");
    sigset_t mask, prev_mask;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);

    /* Заблокировать SIGINT и сохранить прежний набор заблокированных сигналов */
    sigprocmask(SIG_BLOCK, &mask, &prev_mask);

    sleep(2);
    printf("You can't kill me!\n");
    sleep(2);

    /* Восстановить прежний набор заблокированных сигналов, разблокировать SIGINT */
    sigprocmask(SIG_SETMASK, &prev_mask, NULL);
    return 0;
}