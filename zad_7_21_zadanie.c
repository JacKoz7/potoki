#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // for fork(), sleep functions
#include <fcntl.h>  // for open function
#include <sys/types.h> // for mkfifo function
#include <sys/stat.h>  // for mkfifo function
#define BUF_SIZE 2048

int main(int argc, char** argv) {
    pid_t pid;
    char bufor[BUF_SIZE];
    int i;
    int fd;
    const char *fifo_name = "/tmp/my_fifo";

    /* create named pipe (FIFO) */
    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo");
        return EXIT_FAILURE;
    }

    /* fork process */
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) { // child process (server)
        /* open FIFO for write */
        fd = open(fifo_name, O_WRONLY);
        if (fd == -1) {
            perror("open");
            return EXIT_FAILURE;
        }

        /* child process generates 10 lines and writes to the FIFO */
        for (i = 0; i < 10; ++i) {
            snprintf(bufor, BUF_SIZE, "Serwer: wysyłam linie nr %d\n", i);
            write(fd, bufor, strlen(bufor) + 1);
            sleep(1); // delay for 1 second
        }

        close(fd); // close FIFO
    } else { // parent process (client)
        /* open FIFO for read */
        fd = open(fifo_name, O_RDONLY);
        if (fd == -1) {
            perror("open");
            return EXIT_FAILURE;
        }

        /* parent process reads from the FIFO */
        while (read(fd, bufor, BUF_SIZE) > 0) {
            printf("Serwer wysłał: %s", bufor);
            sleep(2); // delay for 2 seconds
        }

        close(fd); // close FIFO

        /* delete FIFO */
        if (unlink(fifo_name) == -1) {
            perror("unlink");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

