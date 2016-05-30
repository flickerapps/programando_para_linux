#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
    pid_t pid1, pid2;
    int status1, status2;
    if( (pid1 = fork()) == 0){ /* el proceso hijo */
        printf("El pid del primer proceso hijo es: %d, su padre es %d\n", getpid(), getppid()); /* PID: Process ID */
    }
    else{ /* el proceso padre */
        if( ( pid2 = fork() ) == 0){ /* proceso hijo 2 */
        printf("El pid del segundo proceso hijo es %d, su padre es %d\n", getpid(), getppid());
        /* PPID = Parent Process ID ( id del padre )*/
        }
        else{ /* proceso padre, otra vez*/
            /* esperamos el proceso 1*/
            waitpid(pid1, &status1, 0);
            /* esperamos el proceso 2 */
            waitpid(pid2, &status2, 0);
            /* Padre, ahora si ya tienes permiso de hablar*/
            printf("El pid del proceso padre es: %d\n", getpid());
        }
    }
    return 0;

    /*
        Ambas llamadas a printf() son asincronas (suena a node.js) es decir se ejecutan en paralelo, por lo tanto no se tiene certeza de que llamada se realize primero (orden de ejecucuion)
    */
}
