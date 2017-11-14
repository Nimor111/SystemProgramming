#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    close(1);

    if ((open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0777)) == -1){
        perror("Error:");
    }

    execvp(argv[2], &argv[2]);

    return 0;
}
