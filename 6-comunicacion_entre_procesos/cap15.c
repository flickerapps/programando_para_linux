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
    pid_t padre, hijo;

    padre = getpid();
    signal(SIGUSR1, trapper);
    if( ( hijo = fork() ) == 0){ /* hijo */
        sleep(1);
        kill(padre, SIGUSR1);
        sleep(1);
        kill(padre, SIGUSR1);
        sleep(1);
        kill(padre, SIGUSR1);
        sleep(1);
        kill(padre, SIGKILL);
        exit(0);
    }
    else{ /* main */
        for(;;);
    }
    return 0;
}

void trapper(int sig){
    signal(sig, trapper);
    printf("SIGUSR1\n");
}
