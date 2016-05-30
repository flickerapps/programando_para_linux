#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char* args[] = {"/bin/ls",NULL}; /* similar a argv[]: el primer argumento es el nombre del programa y luego los parametros (en este caso NULL, es decir, ninguno)*/

    execv("/bin/ls", args); /* path del ejecutable y nosotros mismos le pasamos los argumentos*/

    /* con execv el proceso se reemplaza, si llega al printf es porque nunca se reemplazo*/
    printf("Se ha producido un error en la ejecucion de execv\n");
    return 0;
}
