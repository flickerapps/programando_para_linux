#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>


#define PORT 80
#define ADDRESS "192.168.1.1"
#define KB 1024
int main(int argc, char const *argv[])
{
    int s, tam, numbytes;
    char buff[] = "Hola mundo!\r\n";
    char buffer[ 1 * KB];

    tam = sizeof( sockaddr );

    struct sockaddr_in mysocket;

    mysocket.sin_family = AF_INET;
    mysocket.sin_port = htons(PORT);
    inet_aton(ADDRESS, &(mysocket.sin_addr));
    memset(&(mysocket.sin_zero),'\0',8);

    if( ( s = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("error");
        exit(-1);
    }

    connect( s, (struct sockaddr*)&mysocket, tam);

    numbytes = send(s, buff, strlen(buff), 0);
    printf("[\n\tbytes enviados: %d,\n", numbytes);

    numbytes = recv(s, buffer, 1 * KB , 0);
    printf("\tbytes recibidos: %d\n]\n", numbytes);
    printf(buffer);
    close(s);
    return 0;
}
