#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> // for sleep function
#include <fcntl.h>  // for open function
#define BUF_SIZE 2048

int main(int argc, char** argv) {
    char bufor[BUF_SIZE];
    int i;
    int fd;
    const char *fifo_name = "/tmp/my_fifo";

    /* open FIFO for write */
    fd = open(fifo_name, O_WRONLY);
    if (fd == -1) {
        perror("open");
        return EXIT_FAILURE;
    }

    /* server generates 10 lines and writes to the FIFO */
    for (i = 0; i < 10; ++i) {
        snprintf(bufor, BUF_SIZE, "Serwer: wysyłam linie nr %d\n", i);
        write(fd, bufor, strlen(bufor) + 1);
        sleep(1); // delay for 1 second
    }

    close(fd); // close FIFO

    return EXIT_SUCCESS;
}

