#ifndef SRC_SAVE_H
#define SRC_SAVE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void save(const char* variable, int nb) {  // Changer char* en const char*
    FILE *f = fopen("data.txt", "a+");
    if (f == NULL) {
        printf("Error opening file data.txt\n");
        return;
    }

    char c;
    rewind(f);
    while ((c = fgetc(f)) != EOF) {  // Correction : Assurez-vous d'initialiser 'c' dans la boucle
        int i = 0;
        while (c == variable[i]) {
            if (variable[i + 1] == '\0') {
                long int cursor = ftell(f);
                fclose(f);
                FILE *f_update = fopen("data.txt", "r+");
                fseek(f_update, cursor + 1, SEEK_SET);
                fprintf(f_update, "%d\n", nb);
                fclose(f_update);
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

#endif // SRC_SAVE_H
