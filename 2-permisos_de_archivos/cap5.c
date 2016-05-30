#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
int main(int argc, char const *argv[])
{
    struct stat fileStat; /* estrcutura donde almacenaremos la info del fichero */

    if( ( lstat("test.txt",&fileStat) ) == -1){
        perror("lstat");
        exit(-1);
    }

    printf( "Propiedades del fichero <test.txt>\n");
    printf( "i-nodo: %d\n", fileStat.st_ino );
    printf( "dispositivo: %d, %d\n", major( fileStat.st_dev ), minor( fileStat.st_dev ) );
    printf( "modo: %#o\n", fileStat.st_mode );
    printf( "vinculos: %d\n", fileStat.st_nlink );
    printf( "propietario: %d\n", fileStat.st_uid );
    printf( "grupo: %d\n", fileStat.st_gid );
    printf( "tipo del dispositivo: %d\n", fileStat.st_rdev );
    printf( "tamaño total en bytes: %ld\n", fileStat.st_size );
    printf( "tamaño de bloque preferido: %d\n", fileStat.st_blksize );
    printf( "numero de bloques asignados: %d\n", fileStat.st_blocks );
    printf( "ultima hora de acceso: %s", ctime( &fileStat.st_atime ) );
    printf( "ultima hora de modificación: %s", ctime( &fileStat.st_mtime ) );
    printf( "ultima hora de cambio en inodo: %s", ctime( &fileStat.st_mtime ) );
    return 0;
}
