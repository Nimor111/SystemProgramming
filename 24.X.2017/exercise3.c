// exercise 2 + 3
// create file
// transfer standard output to file
// directly
// with dup

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    close(1);
    ssize_t fd = open(argv[1], O_CREAT|O_TRUNC|O_WRONLY, 0644);
    for (int i = 0; i < 10; ++i) {
        printf("EXAMPLE\n");
    }

    return 0;
}
