#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


struct thr_inf { /* almacenaremos la info. del hilo y las variables del scope padre que queremos cambiar o manejar dentro del hilo */
    pthread_t* p_id; /* id absoluto en el proceso */
    int id; /* id relativo a otros hilos */
    void* var; /* puntero a variable que manejaremos (declarado void para que pueda almacenar cualquier tipo )*/
};

 typedef struct thr_inf hilo_info; /* defino un tipo 'hilo_info' para no tener que usar struct en las declaraciones */


void* FuncionAsincrona(void* hilo){ /* esta funcion se ejecuta Asincronamente */
    hilo_info* h; /* puntero-a estructura hilo_info */
    h = (hilo_info*)hilo; /* utilizo h como apuntador a hilo para poder manejarlo/modificarlo */
    int* var = (int*)h->var; /* casteo la variable a int* para poder manejarla como entero */
    printf("Asincronia en el hilo: %d, var = %d\n", h->id, *var); /* id del hilo y la variable que cambiaremos */
    (*var)++; /* si hago simplemente var++ lo que estaria incrementando sera la posicion de memoria */
    pthread_exit(NULL); /* Salimos del hilo*/
}
int main(int argc, const char* argv[]){
    int var = 10; /* variable del scope padre que manejaremos atraves del hilo */
    pthread_t pth_id; /* p_id de nuestro hilo*/
    hilo_info hilo; /* estructura para la informacion de nuestro hilo */
    hilo.var = (void*)&var; /* almaceno el puntero a var (del scope padre) en la estructura */
    hilo.p_id = &pth_id; /* almaceno el p_id del hilo */
    hilo.id = 0; /* defino mi id relativo como 0 */
    pthread_create(hilo.p_id, NULL, FuncionAsincrona, (void*)&hilo); /* creo el hilo a traves de si p_id, con atributos por defecto, para que ejecute la funcionAsincrona que recibe como argumento el hilo (mi estructura con la info )*/
    printf("Hola, soy el hilo principal.\n"); /* mientras tanto mostramos esto */
    pthread_join(*hilo.p_id, NULL); /* esperamos que termine de ejecutarse el hilo*/
    printf("Ahora 'var' vale: %d\n", var); /* imprimimos el nuevo valor de 'var', ya que lo cambiamos a traves del hilo */
    return 0;
}
