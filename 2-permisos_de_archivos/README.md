chmod y chown
====

Para los permisos de archivos se utiliza chmod(), una funcion con el mismo nombre que el comando que utilizamos en nuestra consola.

Los prototipos son:
```c
int chmod(const char *path, mode_t mode);
int fchmod(int fildes, mode_t mode);
```

Donde mode es el numero entero correspondiente a los valores (ejecucion - lectura - escritura). La diferencia de estas funciones es que la primera recibe el path de un archivo, pero la segunda recibe un `descriptor de fichero`.

Ejemplo:
```c
chmod("/home/user/file.sh",0666);
```

Para modificar su propietario se utilizan las sigtes funciones:
```c
int chown(const char *path, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int lchown(const char *path, uid_t owner, gid_t group);
```

Y ahora si... te acabas de liar, verdad?. Que es esto de `uid_t owner, git_d group`?.

Pues en linux cada usuario del sistema tiene su propio `id` (identificador) y ademas tiene el `id` del grupo al que pertecene. Los usuarios en linux se distribuyen en `grupos de usuarios`. Estos grupos se aprecian en ` /etc/passwd ` y ` /etc/group`.

Volvemos aqui. `chown` y `fchown` se diferencian por lo miso que `chmod` y `fchmod` (la primera recibe el `path` y la segunda el `file descriptor`), pero tambien tenemos `lchown`, esta es identica a `chown` a diferencia que es mas segura ya que no sigue enlaces simbolicos.


stat
====

prototipos de stat:
```c
int stat(const char *file_name, struct stat *buf);
int fstat(int filedes, struct stat *buf);
int lstat(const char *file_name, struct stat *buf);
```

ya sabemos en que se diferencian, cierto?.

con stat necesitamos como parametro un puntero a estructura tipo `stat`:
```c
struct stat {
    dev_t st_dev; /* dispositivo */
    ino_t st_ino; /* numero de inode */
    mode_t st_mode; /* modo del fichero */
    nlink_t st_nlink; /* numero de hard links */
    uid_t st_uid; /* UID del propietario*/
    gid_t st_gid; /* GID del propietario */
    dev_t st_rdev; /* tipo del dispositivo */
    off_t st_size; /* tamaño total en bytes */
    blksize_t st_blksize; /* tamaño de bloque preferido */
    blkcnt_t st_blocks; /* numero de bloques asignados */
    time_t st_atime; /* ultima hora de acceso */
    time_t st_mtime; /* ultima hora de modificación */
    time_t st_ctime; /* ultima hora de cambio en inodo */
};
```
