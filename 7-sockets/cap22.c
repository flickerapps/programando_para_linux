#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define KB 1024
int main(int argc, char const *argv[])
{
    int port, maxcl;
    if( argc == 1 || argc > 3){
        printf("use:\t%s <port> <max-clients>\n", argv[0]);
        exit(1);
    }
    else if(argc == 2){ /* port only*/
        maxcl = 10;
        port = atoi(argv[1]);
    }
    else{
        port = atoi(argv[1]);
        maxcl = atoi(argv[2]);
    }
    int s, nuevo;
    struct sockaddr_in mysocket;

    mysocket.sin_family = AF_INET;
    mysocket.sin_port = htons(port);
    mysocket.sin_addr.s_addr = INADDR_ANY;
    memset( &(mysocket.sin_zero ), '\0', 8);

    if( ( s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("error");
        exit(-1);
    }
    socklen_t tam = sizeof( struct sockaddr );
    bind( s, (struct sockaddr*)&mysocket, tam); /* con bind asociamos el puerto asignado a mysocket, con nuestro socket `s`, de modo que cuando un paquete llegue al ordenador vaya al socket, es decir, creamos un servicio y le asignamos un puerto */

    listen(s, maxcl); /* a la escucha en dicho puerto, el parametro es el max-client*/
    printf("[*] Servidor a la escucha en el %s:%d\n", inet_ntoa(mysocket.sin_addr), ntohs(mysocket.sin_port) );

    while(1){
        nuevo = accept(s, (struct sockaddr*)&mysocket, &tam); /* aceptamos la conexion*/
        printf("Se ha conectado un nuevo cliente\n");
        if( fork() == 0){
            close(s); /* el hijo no necesita el socket padre */
            char msg[] = "200 OK\r\n";
            char buffer[(1 * KB) + (KB/4)];
            int readbytes = recv(nuevo, buffer, 1 * KB, 0);
            printf("Se recibieron %d bytes:\n", readbytes);
            buffer[readbytes] = '\0';
            printf("%s\n", buffer);
            readbytes = send(nuevo, msg, strlen(msg), 0);
            printf("Se enviaron %d bytes\n", readbytes);
            close(nuevo);
            exit(0);
        }
        else{
            close(nuevo); /* el padre no necesita ese nuevo socket*/
        }
    }
    return 0;
}
