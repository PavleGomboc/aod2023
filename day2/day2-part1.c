#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int checkGame(char *input) {
    int colorMap[3] = {12, 13, 14};
    int colorBuffer[3] = {0, 0, 0};
    int digitBuffer;

    char *token = strtok(input, " ");
    while (token != NULL) {
        if (strstr(token, "Game")) {
            token = strtok(NULL, " ");
            continue;
        }

        if (strchr(token, ':')) {
            token = strtok(NULL, " ");
            continue;
        }

        if (isdigit(token[0])) {
            digitBuffer = atoi(token);
            token = strtok(NULL, " ");
            continue;
        }

        if (strstr(token, "red")) {
            if (digitBuffer > colorMap[0]) return 0;
        } else if (strstr(token, "green")) {
            if (digitBuffer > colorMap[1]) return 0;
        } else if (strstr(token, "blue")) {
            if (digitBuffer > colorMap[2]) return 0;
        }

        token = strtok(NULL, " ");
    }

    return 1;
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int idSum = 0, idBuffer;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "Game %d:", &idBuffer);
        if (checkGame(line)) {
            idSum += idBuffer;
        }
    }

    fclose(file);
    printf("Sum of valid game IDs: %d\n", idSum);

    return 0;
}
