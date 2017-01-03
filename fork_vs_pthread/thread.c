#include <stdio.h>
#include <pthread.h>

void *run(void *a) {
    printf("I'm a child\n");
    pthread_exit(0);
}

int main(int argc, char *argv[]) {
    pthread_t thread1;
    int i = 1;
    if (pthread_create(&thread1, NULL, run, &i)) {
        perror("Thread creation");
    }
    pthread_join(thread1, NULL);
    printf("I'm a parent\n");
    printf("I'm back\n");
    return 0;
}
