#include <stdio.h>

int main(int argc, char *argv[])
{
    extern char **environ;
    char **env;

    for ( env=environ; *env != 0; env++ )
        printf("%s\n", *env);

    return 0;
}
