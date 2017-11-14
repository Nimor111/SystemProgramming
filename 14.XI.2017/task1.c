#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if ((execl("/bin/who", "who", 0) == -1 )) {
        printf("Something that won't execute!");
    }

    return 0;
}
