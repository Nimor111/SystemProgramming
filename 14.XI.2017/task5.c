#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // &argv[1] passes rest of argv
    execvp(argv[1], &argv[1]);

    return 0;
}
