/* std */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
/* sockets */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
/* threads */
#include <pthread.h>

/*
 * sockets usando hilos
*/

enum methods_enum{
    HEAD,
    GET,
    POST,
    PUT,
    PATCH,
    DELETE
};
typedef enum methods_enum method_t;

struct cli_request_struct{
    method_t method; /* request method */
    int fd; /* socket file descriptor */
    struct sockaddr_in* saddr;
    socklen_t size; /* sockets size */
};

typedef struct cli_request_struct request_t;

/* prototypes */

void* handleAsync(void*);
void* recvAsync(void*);
void* sendAsync(void*);
void interrupt(int);

 /* end */

/* Glo-vars */

socklen_t socksize = sizeof( struct sockaddr );
const int port = 65535; /* last port */
const int max_cli = 200;
const short zerobits = 8;
int mainSocket;
pthread_mutex_t mutex;
pthread_t tid[3]; /* request, (response) send and (response) receive */


#define KB 1024
/* end */
int main(int argc, char const *argv[])
{
    int s, client, opt;

    struct sockaddr_in mysocket;

    mysocket.sin_family = AF_INET;
    mysocket.sin_port = htons(port);
    mysocket.sin_addr.s_addr = htonl(INADDR_ANY);
    memset( &(mysocket.sin_zero), '\0', zerobits);

    if( (s = socket(PF_INET, SOCK_STREAM, 0) ) < 0){
        perror("socket");
        exit(1);
    }
    opt = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    mainSocket = s;

    bind(s, (struct sockaddr*)&mysocket, socksize);
    listen(s, max_cli);
    printf("Listening on %s:%d\n",
        inet_ntoa(mysocket.sin_addr), port );
    signal(SIGINT, interrupt);
    signal(SIGKILL, interrupt);

    for(;;){
        client = accept(s, (struct sockaddr*)&mysocket, &socksize);
        request_t client_request;
        client_request.method = GET;
        client_request.fd = client;
        client_request.saddr = &mysocket;
        client_request.size = socksize;
        pthread_mutex_init(&mutex, NULL);
        pthread_create(&tid[0], NULL, handleAsync, (void*)&client_request);
    }
    close(s);
    return 0;
}

void interrupt(int sig){
    signal(sig, interrupt);
    printf("\nClosing socket...\nBye!\n");
    close(mainSocket);
    exit(0);
}

void* handleAsync(void* c){
    request_t* client;
    client = (request_t*)c;
    printf("Accepted Connection from %s\n",
        inet_ntoa( (client->saddr)->sin_addr )
    );

    pthread_create(&tid[1], NULL, recvAsync, c);
    pthread_create(&tid[2], NULL, sendAsync, c);

    pthread_join(tid[2], NULL);
    close(client->fd);
    pthread_exit(NULL);
}

void* recvAsync(void *c){
    request_t* client;
    client = (request_t*)c;

    char buffer[KB];
    int recvbytes = recv(client->fd, buffer, KB -1, 0);
    printf("\nRecivied bytes: %d\n", recvbytes);
    printf("----------------- Request -----------------\n\n");
    printf("%s\n", buffer);
    printf("-------------------------------------------\n");
    pthread_exit(NULL);
}

void* sendAsync(void* c){
    request_t* client;
    client = (request_t*)c;

    char message[] =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html;charset=utf-8\r\n"
        "Server: micro-httpd\r\n"
        "Set-Cookie: hello=world; lorem=ipsum\r\n"
        "Connection: close\r\n\r\n"
        "Hello World\r\n";
    pthread_join(tid[1], NULL);
    int sendbytes = send( client->fd, message, strlen(message), 0);
    printf("Sent bytes: %d\n", sendbytes);
    pthread_exit(NULL);
}

