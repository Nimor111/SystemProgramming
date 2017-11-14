// open file for reading
// duplicate descriptor
// read one after the other from both descriptors and print
// close original desc
// continue reading from duplicate desc

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 1024

int main(int argc, char *argv[])
{
    int fd = open("f1.txt", O_RDONLY, 0664);

    int fdup = dup(fd);

    char buf[BUF_SIZE];
    read(fd, buf, 10);

    printf("%s", buf);
    close(fd);
    strcpy(buf, "     ");

    read(fdup, buf, 5);

    printf("\nTHIS IS THE NEW PART\n");
    printf("%s\n", buf);

    return 0;
}
