#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void read(const char* variable) {
    // Ouvrir le fichier en mode lecture seule
    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("Error opening file data.txt\n");
        return;
    }

    char file_var[20];
    int value;
    bool found = false;

    // Parcourir chaque ligne du fichier pour trouver la variable
    while (fscanf(f, "%19[^:]:%d\n", file_var, &value) == 2) {
        if (strcmp(file_var, variable) == 0) {
            printf("%d\n", value);  // Affiche la valeur trouvée
            found = true;
            break;
        }
    }

    if (!found) {
        printf("Variable '%s' not found.\n", variable);
    }

    fclose(f);
}

#ifndef SRC_READ_H
#define SRC_READ_H
#endif //SRC_READ_H
