#include <stdio.h>
#include <pthread.h>

/*
* crearemos un pequeno programa que efectue las 4 operaciones basicas con dos numeros (pudieran
* ser diferentes ) asincronamente, es decir, cada operacion se ejecuta en paralelo
* independientemente de las 3 restantes. Esto usando threads.
*/


/*
 * la estructura guardara los dos numeros, y el signo de la operacion
*/
struct operation{
    int num1;
    int num2;
    int signo;
};

/*
 enumeracion del 0 al 3 con los respectivos valos de los signos para las operaciones
*/
enum signs{
    SUMA,
    RESTA,
    MULTIPLICACION,
    DIVISION
};

typedef struct operation op;
typedef enum signs Signos;


/*
 * funcion que realiza la operacion matematica de acuerdo al signo de la estructura que contiene
 * los datos
 */
void* operationAsync(void *oper){
    op* operacion = (op*)oper; /* casteamos de void a la estructura op */
    int n1 = operacion->num1;
    int n2 = operacion->num2;

    int result = 0;
    /* de aqui en adelante, verificamos cual operacion sea, si es valida efecutamos la correspondiente, de lo contrario imprimimos el error y retornamos 0 */
    switch(operacion->signo){
        case SUMA:
            result = n1+n2;
            printf("%d + %d = %d\n", n1, n2, result);
            break;
        case RESTA:
            result = n1-n2;
            printf("%d - %d = %d\n", n1, n2, result);
            break;
        case MULTIPLICACION:
            result = n1*n2;
            printf("%d * %d = %d\n", n1, n2, result);
            break;
        case DIVISION:
            result = n1/n2;
            printf("%d / %d = %d\n", n1, n2, result);
            break;
        default:
            perror("\n\t[-] Error Al efectuar operacion (SIGNO_NO_VALIDO)\n\n");
    };

    return (void*)result;
}

int main(int argc, char const *argv[]){
    pthread_t tid[4]; /* 4 hilos para las diferentes operaciones */
    op operacion[4]; /* almacena los datos de cada operacion */
    int i = 0;
    for (i = 0; i < 4; ++i)
    {
        operacion[i].num1 = 10;
        operacion[i].num2 = 5;
        operacion[i].signo = i;
        pthread_create(&tid[i], NULL, operationAsync, (void*)&operacion[i]); /* lanzamos el hilo */
    }
    for (i = 0; i < 4; ++i)
    {
        void* res; /* puntero void para guardar cualquier dato */
        pthread_join(tid[i], &res); /* esperamos que finalizen los hilos y el valor que retornen lo almacenamos en res */
        int result = (int)res; /* casteamos el valor de res a entero */
        printf("Resultado en el padre: %d\n", result); /* debo comentar esta linea? */
    }
    return 0;
}
