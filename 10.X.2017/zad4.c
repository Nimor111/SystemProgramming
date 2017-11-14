#include <stdio.h>
#include <stdlib.h>

#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 5

int main(int argc, char *argv[])
{
    int fd;
    if ((fd = open(argv[1], O_RDONLY, 0644)) == -1) {
        printf("Error! Can not open file!\n");
        exit(1);
    };
    int i;
    char buf[BUF_SIZE];

    for ( i = 5; i > 0; i--)
    {
        lseek(fd, -4, SEEK_END);
        if (read(fd, buf, i) == -1)
        {
            printf("Error! Can not read from file!\n");
            exit(1);
        }
        printf("%s", buf);
    }
    printf("\n");

    return 0;
}
