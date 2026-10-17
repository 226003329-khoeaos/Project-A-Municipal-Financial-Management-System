#include <stdio.h>
#include <string.h>
#include "utils.h"

#define BUF 200

int readInt(const char prompt[], int min, int max)
{
    char buffer[BUF];
    char extra;
    int value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, BUF, stdin) != NULL &&
        sscanf(buffer, "%d %c", &value, &extra) == 1 &&
        value >= min && value <= max) {
            return value;
        }
        printf("Invalid  input. Enter a whole number from %d to %d.\n", min, max);
    }
}

double readDouble(const char prompt[], double min)
{
    char buffer[BUF];
    char extra;
    double value;

    while (1) {
        printf("%s", prompt);
        if (fgets(buffer, BUF, stdin) != NULL &&
        sscanf(buffer, "%lf %c", &value, &extra) == 1 &&
        value >= min) {
            return value;
        }
        printf("Invalid input. Enter a number that is at least %.2f.\n", min);
    }
}

void readString(const char prompt[], char dest[], int size)
{ 
    char buffer[BUF];
    int len;

    while (1) {
        printf("%s", prompt);
        if(fgets(buffer, BUF, stdin) != NULL) {
            len = strlen(buffer);
            if (len > 0 && buffer[len - 1] == '\n') {
                buffer[len - 1] = '\0';
                len--;
            }
            if (len == 0) {
                printf("Input cannot be empty.\n");
            } else if (len >= size) {
                printf("Too long. Maximum %d characters.\n", size - 1);
            } else {
                strcpy(dest, buffer);
                return;
            }
        }
    }
}
            