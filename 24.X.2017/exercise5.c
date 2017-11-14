// 10 * EXAMPLE, 10 * 0-10, 10 * HELLO
// put EXAMPLE in file
// 1 - 10 on screen
// 10 * HELLO in file ( same one )

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
    int out_copy = dup(1);
    close(1);
    open("f5.txt", O_CREAT|O_TRUNC|O_WRONLY, 0644);

    for (int i = 0; i < 10; ++i) {
        printf("EXAMPLE\n");
    }

    close(1);
    dup(out_copy);

    for (int i = 1; i < 11; ++i) {
        write(1, "STRING\n", 7);
    }

    close(1);
    open("f5.txt", O_APPEND|O_WRONLY, 0644);

    for (int i = 0; i < 10; ++i) {
        printf("HELLO\n");
    }

    return 0;
}
