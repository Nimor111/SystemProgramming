#include <stdio.h>

void puts_str(char *const);

int main(int argc, char *argv[])
{
    puts_str("ivan\n");
    return 0;
}

void puts_str(char *const msg) {
    fputs(msg, stdout);
}
