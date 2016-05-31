#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define SIZE 512

int main(int argc, char const *argv[])
{
    pid_t pid;
    int p[2], readbytes;
    char buffer[SIZE];

    pipe(p); /* p[0] = read ; p[1] = write*/


    if( (pid = fork()) == 0){ /* hijo */
        close(p[1]); /* cerramos el lado de escribir */
        while( (readbytes = read(p[0], buffer, SIZE)) > 0){
            write(1, buffer, readbytes);
        }

        close(p[0]); /* cerramos la parte de lectura*/

    }
    else{ /* padre */
        close(p[0]); /* cerramos el lado de lectura */
        strcpy(buffer, "Esto se envia a traves de tuberia (pipe)\n");
        write(p[1], buffer, strlen(buffer));
        close(p[1]); /* ya no necesito escribir, lo cierro */
    }
    waitpid(pid, NULL, 0); /* esperamos que el hijo este listo */
    return 0;
}
