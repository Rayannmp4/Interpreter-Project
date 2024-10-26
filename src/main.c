#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "interpret.h"


int main() {
    while (true) {
        char input[50];
        printf("Give us an operation (or type 'exit' to quit): ");
        fgets(input, 50, stdin);

        // Enlever le saut de ligne (\n) à la fin de l'entrée
        input[strcspn(input, "\n")] = '\0';

        // Vérifier si l'utilisateur veut quitter
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Appeler la fonction d'interprétation
        interpret(input);

        // Dans votre fonction main()

    }
    return 0;
}