#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    char buffer[255];
    printf("El direrctorio actual es: %s\n", getcwd(buffer, -1));
    chdir(".."); /* nos movemos un dir. hacia atras */
    mkdir("./mifolder", 0755); /* creamos un folder */
    rmdir("./mifolder"); /* borramos el folder */
    return 0;
}
