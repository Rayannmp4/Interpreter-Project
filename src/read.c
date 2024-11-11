#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "read.h"

void read(const char* variable) {
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("Error opening file data.txt\n");
        return;
    }

    char file_var[20];
    int value;
    bool found = false;

    while (fscanf(f, "%19[^:]:%d\n", file_var, &value) == 2) {
        if (strcmp(file_var, variable) == 0) {
            printf("%d\n", value);
            found = true;
            break;
        }
    }

    if (!found) {
        printf("Variable '%s' not found.\n", variable);
    }

    fclose(f);
}
