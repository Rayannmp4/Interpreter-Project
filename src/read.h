#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void read(char* variable) {
    FILE *f = fopen("data.txt", "a+");
    if (f == NULL) {
        printf("Error opening file data.txt\n");
        return;
    }
    char c;
    rewind(f);
    while (c != EOF) {
        int i = 6;
        c = fgetc(f);
        while (c == variable[i]) {
            if (variable[i+1] == ')') {
                fseek(f, 1, SEEK_CUR);
                int n;
                fscanf(f, "%d", &n);
                printf("%d", n);
                return;
            }
            c = fgetc(f);
            i++;
        }
    }
    fclose(f);
}

#ifndef SRC_READ_H
#define SRC_READ_H
#endif //SRC_READ_H
