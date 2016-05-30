#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char buffer[255];
    printf("El directorio actual es: %s\n", getcwd(buffer, -1));
    return 0;
}
