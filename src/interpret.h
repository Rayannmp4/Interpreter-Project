#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "lexer.h"
#include "parser.h"


Variable variables[100]; // on stocke en max 100 var
int variable_count = 0;  // compteur pour les var

// get la valeur de la variable
int get_val_variable(Variable *variables, int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    printf("Error!!! Variable '%s' not found.  value is 0.\n", name);
    return 0; // Retourne 0 si la variable n'est pas trouvée, mais avec un message d'erreur
}

// Fonction pour mettre à jour ou ajouter une variable
void set_val_variable(Variable *variables, int *count, const char *name, int value) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }
    // Si la variable n'existe pas, on l'ajoute
    strcpy(variables[*count].name, name);
    variables[*count].value = value;
    (*count)++;
}

// Fonction pour interpréter une expression
void interpret(const char* input) {
    // Remplacer l'entrée utilisateur par l'input fourni
    char calcul[50];
    strcpy(calcul, input);

    // Analyser la chaîne de caractères pour savoir s'il y a une assignation
    char *equal_sign = strstr(calcul, "=");
    char *operation = NULL;
    char *variable = NULL;

    if (equal_sign) {
        variable = malloc(sizeof(char) * 20);
        variable[0] = '\0';
        int i = 0;

        // Extraire le nom de la variable (avant le signe "=")
        while (calcul[i] == ' ') i++; // Ignorer les espaces initiaux
        while (calcul[i] != '=' && calcul[i] != ' ' && calcul[i] != '\0') {
            char temp[2];
            temp[0] = calcul[i];
            temp[1] = '\0';
            strcat(variable, temp);
            i++;
        }

        // L'opération après l'assignation
        operation = equal_sign + 1;
    } else {
        // Si pas d'assignation, c'est juste une expression
        operation = calcul;
    }

    // Obtenir la liste des tokens à partir de l'opération
    Token *head = lexer(operation);

    // Calculer le résultat
    int result = 0;

    // Si le premier token est une variable, obtenir sa valeur
    Token *current = head;
    while (current != NULL) {
        if (current->type == TOKEN_VAR) {
            current->my_token.number = get_val_variable(variables, variable_count, current->my_token.var_name);
        }
        current = current->next;
    }

    // Calculer le résultat
    result = parser(head);

    // Afficher ou stocker le résultat
    if (variable) {
        printf("%s = %d\n", variable, result);
        set_val_variable(variables, &variable_count, variable, result);
        free(variable);
    } else {
        printf("Result = %d\n", result);
    }

    // Libérer la mémoire
    while (head != NULL) {
        Token *next = head->next;
        free(head);
        head = next;
    }
}