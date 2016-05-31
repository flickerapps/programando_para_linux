#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

#define PUERTO 80
#define ADDRESS "127.0.0.1"
int main(int argc, char const *argv[])
{
    int s; /* fd del socket */
    struct sockaddr_in mysocket; /* estructura para almacenar los datos del fd de arriba */
    mysocket.sin_family = AF_INET; /* familia de conexion */
    mysocket.sin_port = htons(PUERTO); /* puerto, htons significa: host to network short */
    inet_aton(ADDRESS, &(mysocket.sin_addr)); /* pasamos la IP de string a network (aton) y la almacenamos en sin_addr */
    memset( &(mysocket.sin_zero), '\0', 8); /* rellenamos con caracter nulo sin_zero en 8 bytes */


    if( ( s = socket(AF_INET, SOCK_STREAM, 0) ) < 0){  /* seteamos nuestro fd */
        perror("error");
        exit(-1);
    }

    int tam = sizeof( struct sockaddr);

    connect(s, (struct sockaddr*)&mysocket, tam); /* conectamos el fd `s` a mysocket y pasamos el tamano de la estructura (como en strncpy,... ) */

    return 0;
}
