#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int fd = open("file.txt", O_CREAT|O_RDWR, 0777);

    char *const str = "Hello!";

    write(fd, str, strlen(str));
    lseek(fd, 0, SEEK_SET);

    char buf[strlen(str) + 1];

    read(fd, buf, strlen(str) + 5);

    printf("Buf is: %s\n", buf);

    return 0;
}
