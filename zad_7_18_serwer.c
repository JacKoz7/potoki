#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep function

int main(int argc, char** argv) {
    int i;
    for (i = 0; i < 10; ++i) {
        printf("Serwer: wysyłam linie nr %d\n", i);
        fflush(stdout);
        sleep(1);  // delay for 1 second
    }
    return (EXIT_SUCCESS);
}

