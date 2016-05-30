#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char const *argv[])
{
    chdir("..");  /* atras */
    DIR * dir;
    struct dirent *mi_dirent;
    if( (dir = opendir("./3-directorios") ) == NULL){
        perror("opendir");
        exit(-1);
    }

    while( (mi_dirent = readdir( dir )) != NULL){ /* mientras no sea null guardamos el fichero en la estructura */
        printf("File\t%s\n", mi_dirent->d_name); /* imprimimos el nombre del archivo */
    }
    closedir(dir); /* cerramos el directorio */
    return 0;
}
