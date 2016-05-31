#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>

void trapper(int); /* prototype */

int main(int argc, char const *argv[])
{
    int i;

    for( i = 1; i <= 64 ; i++){
        signal(i, trapper);
    }

    printf("Identificativo del proceso %d\n", getpid() );
    pause();
    printf("Continuando...\n");

    return 0;
}

void trapper(int sig){
    signal(sig, trapper);
    printf("Recibida la signal %d\n", sig);
}
