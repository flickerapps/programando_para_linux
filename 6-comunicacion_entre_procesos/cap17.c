#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#define SIZE 512

int main(int argc, char const *argv[])
{
    int readbytes, p1[2], p2[2];
    pid_t pid;
    pipe(p1);
    pipe(p2);

    if( (pid = fork() ) == 0){ /* hijo */
        close(p1[1]); /* cerramos la escritura en p1 */
        close(p2[0]); /* cerramos la lectura en p2 */
        char buffer[SIZE];
        /* leemos desde el p1[0] y lo mostramos por pantalla */
        while( ( readbytes = read(p1[0], buffer, SIZE)) > 0){
            write(1, buffer, readbytes);
        }
        close(p1[0]);

        /* escribimos en p2[1] para enviarlo */

        char buffer2[SIZE];
        strcpy(buffer2, "Esto se envio desde el hijo, a traves de pipes\n");
        write(p2[1], buffer2, strlen(buffer2));
        close(p2[1]);
    }
    else{ /* padre*/
        close(p1[0]); /* padre no leera de p1, solo escribira */
        close(p2[1]); /* no escribira en p2, solo leera */


        char buffer2[SIZE];
        strcpy(buffer2, "Esto se envio desde el padre hacia el hijo, a traves de pipes\n");
        write(p1[1], buffer2, strlen(buffer2));
        close(p1[1]);

        char buffer[SIZE];
        while( ( readbytes = read(p2[0], buffer, SIZE) ) > 0){
            write(1, buffer, readbytes);
        }
        close(p2[0]);
    }
    waitpid(pid, NULL, 0);
    return 0;
}
