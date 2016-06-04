#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 20 /* maximo numero de hilos */
int count = 0; /* contador global */

pthread_mutex_t mutex; /* mutex para controlar el acceso a un segmento o variable*/

void* asyncFn(void* arg){ /* funcion asincrona */
    pthread_mutex_lock(&mutex); /* bloqueamos el acceso a otros hilos miestras: */
    printf("Hello!! %d\n", count); /* imprimamos el contador */
    count++; /* y lo incrementemos */
    pthread_mutex_unlock(&mutex); /* ya que terminamos la tarea sincrona, desbloqueamos para dar acceso a otros hilos */
    pthread_exit(NULL); /* salimos del hilo */
}

int main(int argc, const char* argv[]){
    pthread_t tid[MAX_THREADS]; /* 20 hilos */
    pthread_mutex_init(&mutex, NULL); /* inicializamos el mutex para poder usarlo */
    int i;
    printf("\n");
    for ( i = 0; i < MAX_THREADS; ++i){
        pthread_create(&tid[i], NULL, asyncFn, NULL); /* lanzamos los hilos */
    }

    for ( i = 0; i < MAX_THREADS; ++i)
    {
        pthread_join(tid[i], NULL); /* esperamos que terminen */
    }
    return 0;
}
