#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if ( argc != 4 ) {
        printf("Usage ./a.out <cmd> <cmd> <filename>\n");
        exit(1);
    }

    pid_t pid = fork();


    if ( pid == 0 ) {
        char *args[] = {argv[2], NULL};
        if (execvp(argv[2], args) == -1) {
            perror("Error ");
            exit(1);
        }
    } else {
        close(1);
        open(argv[3], O_CREAT|O_WRONLY, 0644);
        char *args[] = {argv[1], NULL};
        if (execvp(argv[1], args) == -1) {
            // Must we be this descriptive
            // perror("Error: ") ???
            fprintf(stderr, "Error %d - %s\n", errno, strerror(errno));
            exit(1);
        };
    }

    return 0;
}
