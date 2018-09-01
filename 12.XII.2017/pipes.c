/* System call pipe(pd)
* pd - int pd[2]
* pd[0] = file descriptor for reading from pipe
* pd[1] = file descriptor for writing to pipe
* Ex.1 -> Pipe between 2 commands
* Ex.2 -> Pipe between 2 commands, command line args(no options or args)
* Ex.3 -> Pipe between 2 commands, first one is without args and options
* Ex.4 -> Pipe between 3 commands
**/

#include <unistd.h>
#include <stdio.h>

void ex1() {
    int pd[2];
    pipe(pd);

    if(fork()) {
        close(1);
        dup(pd[1]);
        close(pd[1]);
        close(pd[0]);
        execlp("ls", "ls", 0);
    } else {
        close(0);
        dup(pd[0]);
        close(pd[0]);
        close(pd[1]);
        execlp("grep", "grep", "pipes", 0);
    }
}

void ex3and2(char ** argv) {
    int pd[2];
    pipe(pd);

    if(fork()) {
        close(1);
        dup(pd[1]);
        close(pd[1]);
        close(pd[0]);
        execlp(argv[0], argv[0], 0);
    } else {
        close(0);
        dup(pd[0]);
        close(pd[0]);
        close(pd[1]);
        execvp(argv[1], &argv[1]);
    }
}

void ex4(char ** argv) {
    int pd[2];
    pipe(pd);

    if (fork()) {
        close(1);
        dup(pd[1]);
        close(pd[1]);
        close(pd[0]);
        execlp(argv[0], argv[0], 0);
    } else {
        int pd2[2];
        pd2[0] = pd[0];
        pipe(pd2);

        if (fork()) {
            close(1);
            dup(pd2[1]);
            close(pd2[1]);
            close(pd2[0]);
            execlp(argv[1], argv[1], 0);
        } else {
            close(0);
            dup(pd2[0]);
            close(pd2[0]);
            close(pd2[1]);
            execlp(argv[2], argv[2], 0);
        }
    }
}

// who | sort
int main(int argc, char *argv[])
{
    /* ex1(); */
    /* ex3and2(&argv[1]); */
    ex4(&argv[1]);

    return 0;
}
