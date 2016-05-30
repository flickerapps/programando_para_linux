#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    pid_t pid;

    if( (pid = fork()) == 0){ /* el proceso hijo */
        printf("El pid del proceso hijo es: %d, su padre es %d\n", getpid(), getppid()); /* PID: Process ID */
    }
    else{ /* el proceso padre */
        printf("El pid del proceso padre es: %d\n", getpid());
    }
    return 0;

    /*
        Ambas llamadas a printf() son asincronas (suena a node.js) es decir se ejecutan en paralelo, por lo tanto no se tiene certeza de que llamada se realize primero (orden de ejecucuion)
    */
}
