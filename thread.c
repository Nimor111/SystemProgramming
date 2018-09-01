#include <pthread.h>
#include <stdio.h>

void second_thread() {
    printf("I AM IN SECOND THREAD\n");
    pthread_exit(0);
}

int main(int argc, char *argv[])
{
    printf("I AM IN FIRST THREAD\n");

    pthread_t id;
    void * func_pointer = &second_thread;
    pthread_create(&id, NULL, func_pointer, NULL);
    pthread_join(id, 0);

    return 0;
}

