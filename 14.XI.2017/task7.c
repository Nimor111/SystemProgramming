#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    close(1);

    open(argv[1], O_CREAT|O_WRONLY, 0644);

    char * args[4];

    args[0] = "grep";
    args[1] = "abc";
    args[2] = "ff.txt";
    args[3] = NULL;

    execvp(args[0], &args[0]);

    return 0;
}
