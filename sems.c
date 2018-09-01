#include <fcntl.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <stdio.h>
#include <wait.h>

#define SEM_MODE 0600

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int fd;
int sem_init(key_t, int);
void P(int);
void V(int);
int get_shared(void);
void put_shared(int);

int main(int argc, char *argv[])
{
    key_t key;
    int semid, loop, i, buff;

    if ( argc < 4 ) {
        printf("Usage a.out filename key loops");
        exit(1);
    }

    if ((fd = open(argv[1], O_CREAT|O_TRUNC|O_RDWR|O_CLOEXEC, 0600)) == -1) {
        perror("Open Error ");
        exit(1);
    }

    put_shared(0);

    key = atoi(argv[2]);
    if ((semid = sem_init(key, 1)) == -1) {
        perror("Semaphore Error ");
        exit(1);
    }

    loop = atoi(argv[3]);
    if (fork()) {
        for (i = 1; i < loop; ++i) {
            P(semid);
            buff = get_shared();
            buff += 1;
            put_shared(buff);
            V(semid);
        }
        wait(NULL);
        buff = get_shared();
        printf("Shared counter: %d\n", buff);
        semctl(semid, 0, IPC_RMID, 0); // delete semaphore
    } else {
        for (i = 1; i < loop; ++i) {
            P(semid);
            buff = get_shared();
            buff += 2;
            put_shared(buff);
            V(semid);
        }
    }

    return 0;
}

int sem_init(key_t key, int semval) {
    int semid;
    union semun arg;

    if((semid = semget(key, 1, IPC_CREAT|IPC_EXCL|SEM_MODE)) == -1) {
        perror("Error ");
        exit(1);
    }

    if(semval >= 0) {
        arg.val = semval;
        if ((semctl(semid, 0, SETVAL, arg.val)) == -1) {
            perror("Error ");
            exit(1);
        }
    }

    return semid;
}

void P(int semid) {
    struct sembuf psem = {0, -1, SEM_UNDO};

    if (semop(semid, &psem, 1) == -1) {
        perror("Error ");
        exit(1);
    }
}

void V(int semid) {
    struct sembuf vsem = {0, 1, SEM_UNDO};

    if (semop(semid, &vsem, 1) == -1) {
        perror("Error ");
        exit(1);
    }
}

void put_shared(int i) {
    lseek(fd, 0, SEEK_SET);
    write(fd, &i, sizeof(int));
}

int get_shared(void) {
    int i;
    lseek(fd, 0, SEEK_SET);
    read(fd, &i, sizeof(int));

    return i;
}
