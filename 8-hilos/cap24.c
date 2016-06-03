#include <stdio.h>
#include <pthread.h>

void* FuncionAsincrona(void* hilo_id){
    int hid = (int)hilo_id;
    printf("Asincronia en el hilo: %d\n", hid);
    pthread_exit(NULL);
}
int main(int argc, const char* argv[]){
    pthread_t hilo[5];
    int  i  = 0;
    for (i = 0; i < 5; i++)
    {
        pthread_create(&hilo[i], NULL, FuncionAsincrona, (void*)i);
    }
    printf("Hello\n");
    for (i = 0; i < 5; i++)
    {
        pthread_join(hilo[i], NULL);
    }
    return 0;
}
