#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i;
    for ( i = 0; i < 5; ++i )
        execl("/bin/ls", "ls -l", 0);

    return 0;
}
