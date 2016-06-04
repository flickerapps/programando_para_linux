#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct thr_inf { /* almacena toda la info del hilo */
    pthread_t *p_id; /* identificador del pthread */
    int id; /* id del hilo, relativo a los demas hilos */
    void* var; /* almacena cualquier dato del hilo, lo usaremos para traer al hilo variables del scope padre */
};

typedef struct thr_inf hilo_info; /* tipo 'hilo_info' para obviar el 'struct' en las declaraciones */

void* funcionAsincrona( void* hilo ){
    hilo_info* h; /* declaramos el puntero */
    h = (hilo_info*)hilo; /* dicho puntero 'apuntara' al argumento void, en este caso la estructura */
    int* var = (int*)h->var;
#if DEBUG
    printf("Asincronia en el hilo: %d (%d), var vale: %d.\n",
        h->id,
        (unsigned int)pthread_self(),
        *var
    );
#else
    printf("Asincronia en el hilo: %d, var vale: %d.\n",
        h->id,
        *var
    );
#endif
    (*var)++; /* incrementar var del scope padre */
    pthread_exit(NULL);
}

int main(int argc, const char* argv[]){
    int var = 10; /* variable del scope padre que utilizaremos en los hilos*/
    pthread_t p_id[10]; /* 10 hilos*/
    hilo_info hilo[10]; /* 10 estructuras para cada pid */
    int i;
    for ( i = 0; i < 10; i++){
        hilo[i].id = i; /* el id sera el numero del orden en el array [i]*/
        hilo[i].var = (void*)&var; /* var en el hilo, apunta a var en el padre */
        hilo[i].p_id = &p_id[i];
        pthread_create( hilo[i].p_id, NULL, funcionAsincrona, (void*)&hilo[i]); /* lanzamos el hilo */
    }

    for ( i = 0; i < 10; i++){
        pthread_join( *hilo[i].p_id, NULL); /* esperamos que los hilos terminen para que el padre tambien lo pueda hacer */
    }

    printf("Ahora el valor de 'var' es: %d\n", var);
    return 0;
}
