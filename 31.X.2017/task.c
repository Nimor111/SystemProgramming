/**
 * Race condition woot woot
 * Create and open file for read-write
 * Write 0 in beginning of file // write(fd, &i, sizeof(int))
 * Create 2 processes
 * long loop
 * read digit = i from file
 * in parent proc i+1
 * in child proc i+2
 * write number in file
 * printf who writes and and what it has taken
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    ssize_t fd;
    if ((fd = open("f1.txt", O_CREAT|O_TRUNC|O_RDWR, 0644)) == -1) {
        perror("Fail!");
        exit(1);
    };

    int f = 0;
    if ( write(fd, &f, sizeof(f)) == -1 ) {
        perror("Fail!");
        exit(1);
    }

    pid_t pid;

    if ( (pid = fork() ) < 0){
        perror("Fail!");
        exit(1);
    };

    for ( int i = 0; i < 100; ++i ) {
        int num;
        if ( pid > 0 ) { // parent
            lseek(fd, 0, SEEK_SET);
            read(fd, &num, sizeof(num));
            num += 1;
            printf("%d in parent\n", num);
            write(fd, &num, sizeof(num));
        } else { // child
            lseek(fd, 0, SEEK_SET);
            read(fd, &num, sizeof(num));
            num += 2;
            printf("%d in child\n", num);
            write(fd, &num, sizeof(num));
        }
    }

    return 0;
}
