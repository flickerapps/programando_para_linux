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
    int port;
    if(argc == 1 || argc > 3){
        fprintf(stderr, "use:\t%s <ip> <port>\n", argv[0]); /* to stderr */
        exit(-1);
    }
    else{
        port = atoi(argv[2]);
    }

    int s;
    socklen_t tam = sizeof(struct sockaddr);
    struct sockaddr_in mysocket;

    mysocket.sin_family = AF_INET;
    mysocket.sin_port = htons(port);
    inet_aton( argv[1], &(mysocket.sin_addr) );
    memset( &(mysocket.sin_zero), '\0', 8);

    if( ( s = socket(AF_INET, SOCK_STREAM, 0) ) < 0){
        perror("error");
        exit(-1);
    }

    connect( s, (struct sockaddr*)&mysocket, tam);
    char request[] =
        "GET / HTTP/1.1\r\n"
        "Host: localhost:3000\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux i686; rv:46.0) Gecko/20100101 Firefox/46.0\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8\r\n"
        "Accept-Language: en-US,en;q=0.5\r\n"
        "Accept-Encoding: gzip, deflate\r\n"
        "Connection: keep-alive\r\n";
    int numbytes = send(s, request, strlen(request), 0);
    printf("bytes enviados: %d\n", numbytes);

    char buffer[KB];
    numbytes = recv(s, buffer, KB -1, 0);
    printf("bytes recividos: %d\n", numbytes);
    printf("Recibido: %s\n", buffer);

    close(s);
    return 0;
}
