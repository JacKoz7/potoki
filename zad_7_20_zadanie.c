#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // for fork(), pipe(), and sleep functions
#define BUF_SIZE 2048

int main(int argc, char** argv) {
    int fd[2];
    pid_t pid;
    char bufor[BUF_SIZE];
    int i;

    /* create pipe */
    if (pipe(fd) == -1) {
        perror("pipe");
        return EXIT_FAILURE;
    }

    /* fork process */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) { // child process (server)
        close(fd[0]); // close unused read end

        /* child process generates 10 lines and writes to the pipe */
        for (i = 0; i < 10; ++i) {
            snprintf(bufor, BUF_SIZE, "Serwer: wysyłam linie nr %d\n", i);
            write(fd[1], bufor, strlen(bufor) + 1);
            sleep(1); // delay for 1 second
        }

        close(fd[1]); // close write end of the pipe
    } else { // parent process (client)
        close(fd[1]); // close unused write end

        /* parent process reads from the pipe */
        while (read(fd[0], bufor, BUF_SIZE) > 0) {
            printf("Serwer wysłał: %s", bufor);
            sleep(2); // delay for 2 seconds
        }

        close(fd[0]); // close read end of the pipe
    }

    return EXIT_SUCCESS;
}

