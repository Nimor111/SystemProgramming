#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <wait.h>

#define BUF_SIZE 4096

void write_to_both_files(char *const filename) {
    int fd;
    if(( fd = open(filename, O_CREAT|O_TRUNC|O_RDWR, 0664)) == -1 ){
        perror("Error ");
        exit(1);
    } ;

    int dupd = dup(fd);

    char *const str1 = "I am a student ";
    char *const str2 = "at fmi.";

    if (write(fd, str1, strlen(str1)) == -1) {
        perror("Error ");
        exit(1);
    }

    if (write(dupd, str2, strlen(str2)) == -1) {
        perror("Error ");
        exit(1);
    };

    char buf[BUF_SIZE];
    int n;

    close(fd);

    lseek(dupd, 0, SEEK_SET);
    while (( n = read(dupd, buf, 1) != 0 )) {
        write(1, buf, 1);
    }

    write(1, "\n", 1);
}

void stdout_to_file(char *const filename) {
    int fd;
    close(1);
    if (( fd = open(filename, O_CREAT|O_TRUNC|O_WRONLY, 0664)) == -1 ) {
        perror("Error ");
        exit(1);
    }

    char *const str = "This is a string";

    write(1, str, strlen(str));
}

void stdout_to_file_and_then_back(char *const filename) {
    int dup_out = dup(1);
    close(1);

    int fd;
    if (( fd = open(filename, O_CREAT|O_TRUNC|O_WRONLY, 0664) ) == -1) {
        perror("Error ");
        exit(1);
    }

    char *const str = "I am a string.\n";

    write(1, str, strlen(str));
    close(fd);

    dup(dup_out);

    printf("I am an stdout camera.\n");
}

void fork_exec_from_child() {
    pid_t pid;

    if (( pid = fork() ) == -1) {
        perror("Error ");
        exit(1);
    }

    if ( pid == 0 ) {
        // child
        printf("The child of %d\n", getppid());
        execlp("ls", "-l", 0);
        printf("This will never be executed\n");
    } else {
        // parent
        printf("This is the parent %d\n", getpid());
    }
}

void write_to_file_from_two_processes(char *const filename) {
    pid_t pid;
    int fd;

    if (( fd = open(filename, O_CREAT|O_TRUNC|O_WRONLY, 0664) ) == -1 ) {
        perror("Open error ");
        exit(1);
    }

    if (( pid = fork() ) == -1 ) {
        perror("Error ");
        exit(1);
    }

    char *const str1 = "I am a child and i'm writing to file\n";
    char *const str2 = "I am a parent and i'm writing to file\n";

    if ( pid == 0 ) {
        // child
        for ( int i = 0; i < 10; ++i ) {
            if ( write(fd, str1, strlen(str1)) == -1 ) {
                perror("Error ");
                exit(1);
            }
        }
    } else {
        // parent
        int status;
        wait(&status);
        printf("Status is %d\n", status);

        for ( int i = 0; i < 10; ++i ) {
            if ( write(fd, str2, strlen(str2)) == -1 ) {
                perror("Error ");
                exit(1);
            }
        }
    }
}

int main(int argc, char *argv[])
{
    /* write_to_both_files("file1.txt"); */
    /* stdout_to_file("file2.txt"); */
    /* stdout_to_file_and_then_back("file3.txt"); */
    /* fork_exec_from_child(); */
    /* write_to_file_from_two_processes("file5.txt"); */

    return 0;
}
