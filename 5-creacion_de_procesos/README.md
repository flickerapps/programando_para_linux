Una situación muy habitual dentro de un programa es la de crear un
nuevo proceso que se encargue de una tarea concreta, descargando al
proceso principal de tareas secundarias que pueden realizarse
asíncronamente o en paralelo. Linux ofrece varias funciones para realizar
esto: `system()` , `fork()` y `exec()` .
Con system() nuestro programa consigue detener su ejecución para llamar
a un comando de la shell (“ /bin/sh ” típicamente) y retornar cuando éste haya
acabado. Si la shell no está disponible, retorna el valor 127, o –1 si se
produce un error de otro tipo. Si todo ha ido bien, system() devuelve el valor
de retorno del comando ejecutado. Su prototipo es el siguiente:
```c
int system(const char *string);
```
Donde “ string ” es la cadena que contiene el comando que queremos ejecutar, por ejemplo:
```c
system(“clear”);
```
Esta llamada limpiaría de caracteres la terminal, llamando al comando
`clear`. Este tipo de llamadas a system() son muy peligrosas, ya que si no
indicamos el PATH completo (“ /usr/bin/clear ”), alguien que conozca nuestra
llamada (bien porque analiza el comportamiento del programa, bien por usar
el comando strings , bien porque es muy muy muy sagaz), podría modificar el
PATH para que apunte a su comando clear y no al del sistema (imaginemos que
el programa en cuestión tiene privilegios de root y ese clear se cambia por
una copia de /bin/sh : el intruso conseguiría una shell de root).
La función system() bloquea el programa hasta que retorna, y además
tiene problemas de seguridad implícitos, por lo que desaconsejo su uso más
allá de programas simples y sin importancia.

La segunda manera de crear nuevos procesos es mediante `fork()` Esta
función crea un proceso nuevo o “proceso hijo” que es exactamente igual
que el “proceso padre”. Si `fork()` se ejecuta con éxito devuelve:

* Al padre: el PID del proceso hijo creado.
* Al hijo: el valor 0.

Para entendernos, `fork()` clona los procesos (bueno, realmente es clone ( )
quien clona los procesos, pero fork() hace algo bastante similar). Es como una
máquina para replicar personas: en una de las dos cabinas de nuestra
máquina entra una persona con una pizarra en la mano. Se activa la máquina
y esa persona es clonada. En la cabina contigua hay una persona idéntica a
la primera, con sus mismos recuerdos, misma edad, mismo aspecto, etc. pero
al salir de la máquina, las dos copias miran sus pizarras y en la de la persona
original está el número de copia de la persona copiada y en la de la “persona
copia” hay un cero.

Si quisiéramos que el
padre esperara a alguno de sus hijos deberemos dotar de sincronismo a este
programa, utilizando las siguientes funciones:
```c
pid_t wait(int *status)
pid_t waitpid(pid_t pid, int *status, int options);
```
La primera de ellas espera a cualquiera de los hijos y devuelve en la
variable entera “status” el estado de salida del hijo (si el hijo ha acabado su
ejecución sin error, lo normal es que haya devuelto cero). La segunda
función, waitpid() , espera a un hijo en concreto, el que especifiquemos en
“ pid ”. Ese PID o identificativo de proceso lo obtendremos al hacer la llamada
a fork() para ese hijo en concreto, por lo que conviene guardar el valor
devuelto por fork() .

Otra manera de crear nuevos procesos, bueno, más bien de modificar los
existentes, es mediante el uso de las funciones exec ( ) . Con estas funciones lo
que conseguimos es reemplazar la imagen del proceso actual por la de un
comando o programa que invoquemos, de manera similar a como lo
hacíamos al llamar a sys tem( ) . En función de cómo queramos realizar esa
llamada, elegiremos una de las siguientes funciones:
```c
int execl( const char *path, const char *arg, ...);
int execlp( const char *file, const char *arg, ...);
int execle( const char * path, const char *arg , ...,
char * const envp[]);
int execv( const char * path, char *const argv[]);
int execvp( const char *file, char *const argv[]);
int execve (const char *filename, char *const argv [],
char *const envp[]);
```
El primer argumento es el fichero ejecutable que queremos llamar. Las
funciones que contienen puntos suspensivos en su declaración indican que
los parámetros del ejecutable se incluirán ahí, en argumentos separados. Las
funciones terminadas en “e” ( exec le ( ) y execve ( ) ) reciben un último argumento
que es un puntero a las variables de entorno. Un ejemplo sencillo nos sacará
de dudas:
```c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
char *args[] = { "/bin/ls", NULL };
execv("/bin/ls", args);
printf("Se ha producido un error al ejecutar execv.\n");
}
return 0;
```
La función elegida, execv( ) , recibe dos argumentos, el path al fichero
ejecutable (“ / b in / ”)
l s y un array con los parámetros que queremos pasar. Este
array tiene la misma estructura que argv[] , es decir, su primer elemento es el
propio programa que queremos llamar, luego se va rellenando con los
argumentos para el programa y por último se finaliza con un puntero nulo
( NULL ). El printf() final no debería salir nunca, ya que para ese entonces execv()
se habrá encargado de reemplazar la imagen del proceso actual con la de la
llamada a “ /bin/ls ”.
