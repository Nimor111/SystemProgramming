#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

void lseek_shenags()
{
    int fd;
    if ((fd = open("test.txt", O_CREAT | O_RDONLY, 0644)) == -1) {
        perror("Open error: ");
        exit(1);
    }

    if (lseek(fd, 3, SEEK_CUR) == -1) {
        perror("Lseek error: ");
        exit(1);
    }

    if (lseek(fd, 2, SEEK_SET) == -1) {
        perror("Lseek error: ");
        exit(1);
    }

    char buffer[2];
    if (read(fd, buffer, 2) == -1) {
        perror("Read error: ");
        exit(1);
    }

    if (write(1, buffer, 2) == -1) {
        perror("Write error: ");
        exit(1);
    }
    write(1, "\n", 1);
}

void lseek_shenags2()
{
    int fd = open("test.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    write(fd, "test", 4);

    char buffer[1];
    lseek(fd, -1, SEEK_END);
    read(fd, buffer, 1);
    write(1, buffer, 1);
    write(1, "\n", 1);
}

int get_status() {
    pid_t pid;
    if ((pid = fork()) < 0) {{
        perror("Fork error: ");
        exit(1);
    }}

    if(!pid) {
        execlp("ls", "ls", 0);
    }
}

int main(int argc, char* argv[])
{
    /* lseek_shenags() */
    /* lseek_shenags2(); */

    return 0;
}
