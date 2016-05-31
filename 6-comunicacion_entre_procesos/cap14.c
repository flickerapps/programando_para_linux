#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

void trapper(int);

int main(int argc, char const *argv[])
{
    int i;

    signal(14, trapper);

    printf("PID: %d\n", getpid());
    alarm(5); /* esperamos 5 seg*/
    pause(); /* recepcion de una signal */
    alarm(3); /* 3 seg */
    pause(); /* esperar signal */
    for(;;){
        alarm(1); /* ahora esperamos solo 1 seg*/
        pause(); /* recepcion de senal*/
    }
    return 0;
}

void trapper(int sig){
    signal(sig, trapper);
    printf("RIINGG\n");
}
