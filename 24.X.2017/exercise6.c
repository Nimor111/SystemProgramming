// copy f1 into f2 with dup
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    close(0);
    close(1);

    int in = open(argv[1], O_RDONLY, 0644);
    int out = open(argv[2], O_WRONLY, 0644);

    return 0;
}
