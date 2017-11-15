#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 4096
#define TESTING 100

int main(int argc, char *argv[])
{
    int fd = open("f.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);

    const char * str = "Hello world!";

    write(fd, str, strlen(str));

    lseek(fd, 10, SEEK_END);

    write(fd, str, strlen(str));

    return 0;
}
