#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int wordToDigit(const char *word, int length) {
    char temp[10];
    if (length >= sizeof(temp)) return -1;
    strncpy(temp, word, length);
    temp[length] = '\0';

    if (strcmp(temp, "one") == 0) return 1;
    else if (strcmp(temp, "two") == 0) return 2;
    else if (strcmp(temp, "three") == 0) return 3;
    else if (strcmp(temp, "four") == 0) return 4;
    else if (strcmp(temp, "five") == 0) return 5;
    else if (strcmp(temp, "six") == 0) return 6;
    else if (strcmp(temp, "seven") == 0) return 7;
    else if (strcmp(temp, "eight") == 0) return 8;
    else if (strcmp(temp, "nine") == 0) return 9;
    return -1;
}

void processString(const char *str, int *firstDigit, int *lastDigit, int startIndex, int *foundFirst) {
    int len = strlen(str);
    if (startIndex >= len) return;

    for (int i = startIndex; i < len; ++i) {
        if (isdigit(str[i])) {
            int digit = str[i] - '0';
            if (!*foundFirst) {
                *firstDigit = digit;
                *foundFirst = 1;
            }
            *lastDigit = digit;
        } else if (isalpha(str[i])) {
            for (int j = i + 1; j <= len; ++j) {
                int digit = wordToDigit(str + i, j - i);
                if (digit != -1) {
                    if (!*foundFirst) {
                        *firstDigit = digit;
                        *foundFirst = 1;
                    }
                    *lastDigit = digit;
                    processString(str, firstDigit, lastDigit, j, foundFirst);
                    return;
                }
            }
        }
    }
}

int main() {
    FILE *file = fopen("cal.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[1024];
    int totalSum = 0;

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        int firstDigit = -1, lastDigit = -1, foundFirst = 0;
        processString(line, &firstDigit, &lastDigit, 0, &foundFirst);

        if (firstDigit != -1 && lastDigit != -1) {
            int value = firstDigit * 10 + lastDigit;
            // printf("DEBUG: Line: %s - First Digit: %d, Last Digit: %d, Combined Value: %d\n", line, firstDigit, lastDigit, value);
            totalSum += value;
        } else {
            // printf("DEBUG: Line: %s - Invalid line (missing first or last digit)\n", line);
        }
    }

    fclose(file);
    printf("Total sum of calibration values: %d\n", totalSum);
    return 0;
}
