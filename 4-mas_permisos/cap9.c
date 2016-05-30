#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    uid_t uid, euid;

    uid = getuid(); /* conseguimos el uid */
    euid = geteuid(); /* conseguimos el euid */

    setreuid(euid, euid); /* asignamos euid */
    system("/bin/bash"); /* llamamos a bash */
    return 0;
}
