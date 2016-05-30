#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define STDOUT 1
#define SIZE 512
int main(int argc, char const *argv[])
{
    int fd, readbytes; /* file descriptor */

    if( (fd = open("test2.txt", O_RDWR) ) == -1 ){
        perror("open");
        exit(-1);
    }

    char buff[SIZE];
    lseek(fd, 255, SEEK_SET); /* nos saltamos 255 bytes luego del comienzo */
    /*
     * SEEK_SET -> desde el principio.
     * SEEK_CUR -> desde donde esta posicionado el cursor (current).
     * SEEK_END -> desde el final.
     */
    while(  ( readbytes = read(fd, buff, SIZE) ) != 0){
        write(STDOUT, buff, readbytes);
    }

    close(fd);
    return 0;
}
