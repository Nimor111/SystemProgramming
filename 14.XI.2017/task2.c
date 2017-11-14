#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if ( execl("/bin/cd", "cd", "-s", 0) == -1) {
        perror("Error...");
    }

    return 0;
}
