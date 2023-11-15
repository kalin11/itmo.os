#include "user/user.h"
#include "kernel/param.h"
#include "kernel/types.h"

int main() {
    int n;

    printf("forktest2: ");

    for (n = 0; n < NPROC + 1; n++) {
        int pid = fork();
        if (pid == 0) {
            continue;
        } else if (pid < 0) {
            printf("failed\n");
            exit(1);
        }
        int status;
        wait(&status);
        exit(status);
    }

    printf("passed\n");
    exit(0);
}