Un descriptor de fichero es un `id` que representa el numero (de orden) que le corresponde a cada fichero abierto en un proceso, asi, por defecto se define `STDOUT` como 1, `STDIN` como 2, y `STDERR` como 3. Es decir, los ficheros que vayamos abriendo, tendran un `file descriptor` mayor que 3.
prototipos de syscalls con descriptores de ficheros:

```c
int creat( const char *pathname, mode_t mode )
int open( const char *pathname, int flags )
int open( const char *pathname, int flags, mode_t mode )
```

Ejemplo:
```c
int fd = open("mi_archivo.txt", O_RDONLY); /* solo lectura */
```
Nota: al principio es confuso porque tendemos a pensar que `fd` almacena el archivo que devuelve `open()`, pero... es un `int`, como pasa esto?. La respuesta es: `open() devuelve el descriptor de fichero correspondiente al archivo que se ha abierto`.

Piensa en esto como un array, Lo que devuelve open es el index del elemento (un arreglo de ficheros) donde se almacena el archivo, y a traves de ese index puedes pasarselo a funciones como `write()` o `read()` para que ellos hagan: `array[fd]`.

el pathname es el nombre del archivo y flags es la manera de como abriremos dicho archivo (para leerlo, escribir, etc.). Flags puede tener los siguientes valores, se puede usar tanto el indicador (constante) como su valor numerico.

Ejemplo con identificador como flag:
```c
int fd = open("mi_archivo2.txt", O_RDONLY); /* solo lectura */
```
o su valor numerico"
```c
int fd = open("mi_archivo.txt", 0);
```

| Indicador | Valor | Descripcion |
| --------- |:-----:| ----------- |
| O_RDONLY | 0000 | sólo para lectura. |
| O_WRONLY | 0001 | sólo para escritura. |
| O_RDWR | 0002 | para lectura y escritura. |
| O_RANDOM | 0010 |  aleatoria (típico de discos). |
| O_SEQUENTIAL |  0020 | secuencial (típico de cintas). |
| O_TEMPORARY | 0040 | carácter temporal. |
| O_CREAT | 0100 | deberá ser creado si no existía previamente. |
| O_LARGEFILE | 100000 | Utilizado sólo para ficheros extremadamente grandes. |
| O_DIRECTORY | 200000 | El fichero debe ser un directorio. |

