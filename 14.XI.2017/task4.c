#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    execl("/bin/ls", "ls", "-l", "/home/gbojinov/", 0);

    return 0;
}
