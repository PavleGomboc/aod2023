#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 1024

int calculatePower(char *input) {
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

        if (strstr(token, "red") && digitBuffer > colorBuffer[0]) colorBuffer[0] = digitBuffer;
        else if (strstr(token, "green") && digitBuffer > colorBuffer[1]) colorBuffer[1] = digitBuffer;
        else if (strstr(token, "blue") && digitBuffer > colorBuffer[2]) colorBuffer[2] = digitBuffer;

        token = strtok(NULL, " ");
    }

    return colorBuffer[0] * colorBuffer[1] * colorBuffer[2];
}

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int powerSum = 0;

    while (fgets(line, sizeof(line), file)) {
        powerSum += calculatePower(line);
    }

    fclose(file);
    printf("Sum of power of minimum sets: %d\n", powerSum);

    return 0;
}
