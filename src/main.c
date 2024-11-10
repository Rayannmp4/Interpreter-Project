#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "interpret.h"
#include "read.h"
void interpret_file(const char *filename) {
    FILE *file = fopen(filename, "r");  // Ouvrir le fichier en mode lecture
    if (file == NULL) {
        printf("Could not open file %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = '\0';  // Supprime le caractère '\n' de la fin de la ligne
        interpret(line);  // Interpréter chaque ligne lue
    }

    fclose(file);  // Fermer le fichier après la lecture
}

int main(int argc, char *argv[]) {
    if (argc == 2) {
        // Si un argument est passé, interpréter les instructions du fichier
        interpret_file(argv[1]);
    } else {
        // Mode interactif si aucun fichier n'est fourni en argument
        while (true) {
            char input[50];
            printf("Give us an operation (or type 'exit' to quit): ");
            fgets(input, 50, stdin);
            input[strcspn(input, "\n")] = '\0';

            if (strcmp(input, "exit") == 0) {
                break;
            }

            if (strncmp(input, "print(", 6) == 0 && input[strlen(input) - 1] == ')') {
                input[strlen(input) - 1] = '\0';
                char *variable = input + 6;
                read(variable);
                printf("\n");
            } else {
                interpret(input);
            }
        }
    }
    return 0;
}
