#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void save(char* variable, int nb) {
    FILE *f = fopen("data.txt", "a+");
    if (f == NULL) {
        printf("Error opening file data.txt\n");
        return;
    }

    char c;
    rewind(f);
    while (c != EOF) {
        int i = 0;
        c = fgetc(f);
        while (c == variable[i]) {
            if (variable[i + 1] == '\0') {
                long int cursor = ftell(f);
                fclose(f);
                FILE *f = fopen("data.txt", "r+");
                fseek(f, cursor+1, SEEK_SET);
                fprintf(f, "%d\n", nb);

                fclose(f);
                return;
            }
            c = fgetc(f);
            i++;
        }
    }

    fputs(variable, f);
    fputc(':', f);
    fprintf(f, "%d\n", nb);
    fclose(f);
}

#ifndef SRC_SAVE_H
#define SRC_SAVE_H
#endif //SRC_SAVE_H
