#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // for sleep function
#define BUF_SIZE 2048

int main(int argc, char** argv) {
    /* trying to run command */
    FILE *command_result = popen("./zad_7_18_serwer", "r");
    if (command_result) {
        char bufor[BUF_SIZE];
        /* reading output line */
        while (fgets(bufor, BUF_SIZE, command_result) != NULL) {
            sleep(2);  // delay for 2 seconds
            printf("Serwer wysłał: %s", bufor);
        }
        /* end of readiing results */
        pclose(command_result);
        fflush(stdout);
        return EXIT_SUCCESS;
    } else {
        printf("Niepowodzenie funkcji popen \n");
        fflush(stdout);
        return EXIT_FAILURE;
    }
}

