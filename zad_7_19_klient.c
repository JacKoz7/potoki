#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strstr function
#define BUF_SIZE 2048

int main(int argc, char** argv) {
    /* trying to run command */
    FILE *command_result = popen("./serwer", "r");
    if (command_result) {
        char bufor[BUF_SIZE];
        int line_number;

        /* reading output line */
        while (fgets(bufor, BUF_SIZE, command_result) != NULL) {
            /* if "file" was not finished */

            /* parse the line number from server message and print it */
            sscanf(bufor, "Serwer: wysyłam linie nr %d", &line_number);
            printf("%d\n", line_number);
        }

        /* end of reading results */
        pclose(command_result);
        fflush(stdout);
        return EXIT_SUCCESS;
    } else {
        printf("Niepowodzenie funkcji popen \n");
        fflush(stdout);
        return EXIT_FAILURE;
    }
}

