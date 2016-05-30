Trabajar con ficheros como lo hemos hecho antes no es suficiente, a veces tenemos que trabajar con directorios (leer, borrar, saltarlos,  o recorrerlos).

```c
char *getcwd(char *buf, size_t size);
char *get_current_dir_name(void);
char *getwd(char *buf);
```
La función getcwd() devuelve una cadena de caracteres con la ruta
completa del directorio de trabajo actual, que almacenará en el buffer “ buf ”,
de tamaño “ size ”. Si el directorio no cabe en el buffer, retornará NULL , por lo
que es conveniente usar alguna de las otras dos funciones.

Si lo que queremos es movernos de directorios usamos:
```c
int chdir(const char *path);
int fchdir(int fd);
```

Para crear y borrar directorios:
```c
int mkdir(const char *pathname, mode_t mode);
int rmdir(const char *pathname);
```

ya eres `pro` leyendo este tipo de funciones, ni tengo que explicarlas...

Los directorios contienen funciones similares a `open`,`read` y `write` en los ficheros, pero terminando en `dir`.

```c
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dir);
int closedir(DIR *dir);
```

Con la primera de ellas conseguimos una variable de tipo DIR en función
de una ruta definida por la cadena de caracteres “ name ”. Una vez obtenida
dicha variable de tipo DIR , se la pasamos como parámetro a la función
readdir() , que nos proporcionará un puntero a una estructura de tipo dirent , es
decir, a la entrada del directorio en concreto a la que hemos accedido. En
esa estructura dirent tendremos todos los datos de la entrada de directorio
que a la que estamos accediendo: inodo, distancia respecto del comienzo de
directorio, tamaño de la entrada y nombre:
```c
struct dirent {
    ino_t d_ino; // numero de i-node de la entrada de directorio
    off_t d_off; // offset
    wchar_t d_reclen; // longitud de este registro
    char d_name[MAX_LONG_NAME+1] // nombre de esta entrada
}
```
