#include "kernel/types.h"
#include "user/user.h"

void main() {

    int p1[2]; // parent
    int p2[2]; // child

    pipe(p1);
    pipe(p2);

    char *PING = "ping";
    char *PONG = "pong";

    int process = fork();
    int child = getpid();

    if (process > 0) {
        // прочитать ответ и вывести его
        close(p1[0]);
        write(p1[1], PING, sizeof(PING));
        close(p1[0]);
        close(p1[1]);
        char *buff[sizeof(PING)];
        read(p2[0], buff, sizeof(PING));
        close(p2[0]);
        fprintf(1, "I'm a parent - %d: got %s\n", child, buff);
    } else if (process == 0) {
        // прочитать ответ, вывести его и отправить pong в ответ
        close(p1[1]);
        char *buff[sizeof(PING)];
        read(p1[0], buff, sizeof(PING));
        close(p1[0]);
        fprintf(1, "I'm a child - %d: got %s\n", child, buff);
        close(p2[0]);
        write(p2[1], PONG, sizeof(PONG));
        close(p2[1]);

    } else {
        fprintf(1, "Failed.");
        close(p1[0]);
        close(p1[1]);
        close(p2[0]);
        close(p2[1]);
    }

    exit(0);

}