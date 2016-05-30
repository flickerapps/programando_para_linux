#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int args, const char* argv[]){
    int fd; /* descriptor de fichero en el proceso actual  */
    if(  (fd = open("test.txt", O_RDWR) ) == -1  ){
        perror("open");
        exit(-1);
    }

    printf("El fichero abierto tiene el descriptor %d\n", fd);
    close(fd); /* cerramos el archivo mediante su fd */

    return 0;
}
