#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // for sleep function
#include <fcntl.h>  // for open function
#include <sys/types.h> // for mkfifo function
#include <sys/stat.h>  // for mkfifo function
#define BUF_SIZE 2048

int main(int argc, char** argv) {
    char bufor[BUF_SIZE];
    int fd;
    const char *fifo_name = "/tmp/my_fifo";

    /* create named pipe (FIFO) */
    if (mkfifo(fifo_name, 0666) == -1) {
        perror("mkfifo");
        return EXIT_FAILURE;
    }

    /* open FIFO for read */
    fd = open(fifo_name, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    /* client reads from the FIFO */
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

    return EXIT_SUCCESS;
}

