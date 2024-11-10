#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "interpret.h"
#include "read.h"

int main() {
    while (true) {
        char input[50];
        printf("Give us an operation (or type 'exit' to quit): ");
        fgets(input, 50, stdin);
        input[strcspn(input, "\n")] = '\0';

        // Vérifiez si l'utilisateur veut quitter
        if (strcmp(input, "exit") == 0) {
            break;
        }

        // Vérifiez si l'utilisateur a entré une commande `print`
        if (strncmp(input, "print(", 6) == 0 && input[strlen(input) - 1] == ')') {
            // Extraire le nom de la variable entre les parenthèses
            input[strlen(input) - 1] = '\0';  // Retirer le dernier caractère ')'
            char *variable = input + 6;       // Obtenir la sous-chaîne après "print("
            read(variable);                   // Appeler la fonction read pour afficher la valeur
            printf("\n");
        } else {
            // Appeler la fonction `interpret` pour traiter les expressions et les calculs
            interpret(input);
        }
    }
    return 0;
}
