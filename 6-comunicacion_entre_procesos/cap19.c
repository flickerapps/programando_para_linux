#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <limits.h>

#define SIZE PIPE_BUF
int main(int argc, char const *argv[])
{
    FILE *file; /* puntero a archivo */
    char command[] = "ls .";
    char buffer[PIPE_BUF];

    file = popen(command, "r"); /* abrimos un pipe, con el comando para su posterior lectura ("r")*/
    /* con el puntero a FILE hacemos todo lo que tuvimos que hacer en el cap18.c , este crea el proceso hijo, crea el pipe, duplica los file descriptors y nos devuelve un puntero al fd resultante */
    while( !feof(file)){ /* mientras no sea el caracter eof = End Of File (fin de fichero) */
        fscanf(file, "%s", &buffer); /* formateamos la entrada y almacenamos en buffer */
        printf("%s\n", buffer); /* como cualquier printf */
    }
    pclose(file);
    return 0;
}
