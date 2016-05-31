#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define STDIN 0
#define STDOUT 1
#define cmdCat "/bin/cat"
#define cmdWc "/usr/bin/wc"

int main(int argc, char const *argv[])
{
    int p[2];
    pid_t pid;

    pipe(p);

    if( ( pid = fork() ) == 0){ /* Hijo */

        close(p[0]); /* cerramos la lectura, solo escribiremos */
        dup2(p[1], STDOUT); /* duplicamos a la escritura del pipe en STDOUT, ahora stdout no es la consola, sino p[1], lo que mandemos a escribir por consola, se ira  a p[1] */
        close(p[1]); /* no lo necesito, ahora es stdout */

        execlp(cmdCat, cmdCat, "cap17.c", NULL); /* recuerda que con exec, sustituimos el proceso con el proceso del comando */
        /* el comando no se pasa dos veces, sino que uno es el path del ejecutable, y otro es el comando (llevan el mismo nombre)*/

        perror("error"); /* si estamos aqui, algo anduvo mal */
        _exit(-1); /* salir sin fflush */
    }
    else{ /* Padre */
        close(p[1]); /* cerramos la escritura del pipe */
        dup2(p[0], STDIN);  /* duplicamos, ahora mi stdin sera lo que lea el pipe */
        close(p[0]); /* no necesito p[0] */

        execlp(cmdWc, cmdWc, NULL); /* el comando no se pasa dos veces, sino que uno es el path del ejecutable, y otro es el comando (llevan el mismo nombre)*/

        perror("error"); /* algo salio mal */
        exit(1); /* salir con fflush char buffer2[SIZE];
        strcpy(buffer2, "Esto se envio desde el padre hacia el hijo, a traves de pipes");
        write(p1[1], buffer2, strlen(buffer2));
        close(p1[1]);*/
    }
    return 0;
}
