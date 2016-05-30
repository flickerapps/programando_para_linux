#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define STDOUT 1
#define SIZE 255
int main(int args, const char* argv[]){

    int fd, readbytes;

    if( (fd = open("test.txt",O_RDWR)) == -1){
        perror("open");
        exit(-1);
    }

    char buffer[SIZE];

    while( (readbytes = read(fd, buffer, SIZE) ) != 0){
       /* write(STDOUT, buffer, SIZE); */ /* con SIZE espera leer ese tamano, no readbytes por lo que imprime basura de memoria. */
        write(STDOUT, buffer, readbytes);
        printf("Bytes Leidos: %d\n", readbytes);
    }


    close(fd);

    return 0;
}
