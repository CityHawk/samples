#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    pid_t pid;
    pid = fork();

    if (pid == 0) {
        printf("I'm a child\n");
    } else {
        printf("I'm a parent\n");
        waitpid(pid);
    }
    printf("I'm back\n");

    return 0;
}
