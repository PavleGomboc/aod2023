#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    FILE *file = fopen("cal.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[100];
    int totalSum = 0;

    while (fgets(line, sizeof(line), file)) {
        int firstDigit = -1, lastDigit = -1;
        for (int i = 0; line[i] != '\0'; i++) {
            if (isdigit(line[i])) {
                if (firstDigit == -1) {
                    firstDigit = line[i] - '0';
                }
                lastDigit = line[i] - '0';
            }
        }

        if (firstDigit != -1 && lastDigit != -1) {
            totalSum += firstDigit * 10 + lastDigit;
        }
    }

    fclose(file);
    printf("Total sum of calibrated values: %d\n", totalSum);
    return 0;
}
