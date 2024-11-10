#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "lexer.h"
#include "parser.h"
#include "save.h"

Variable variables[100]; // on stocke en max 100 variables
int variable_count = 0;

// get la valeur de la variable
int get_val_variable(Variable *variables, int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    printf("Error!!! Variable '%s' not found. Value is 0.\n", name);
    return 0;
}

// Fonction pour mettre à jour ou ajouter une variable
void set_val_variable(Variable *variables, int *count, const char *name, int value) {
    for (int i = 0; i < *count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }
    strcpy(variables[*count].name, name);
    variables[*count].value = value;
    (*count)++;
}

// Fonction pour interpréter une expression
void interpret(const char* input) {
    char calcul[50];
    strcpy(calcul, input);

    char *equal_sign = strstr(calcul, "=");
    char *operation = NULL;
    char *variable = NULL;

    if (equal_sign) {
        variable = malloc(sizeof(char) * 20);
        variable[0] = '\0';
        int i = 0;
        while (calcul[i] == ' ') i++;
        while (calcul[i] != '=' && calcul[i] != ' ' && calcul[i] != '\0') {
            char temp[2];
            temp[0] = calcul[i];
            temp[1] = '\0';
            strcat(variable, temp);
            i++;
        }
        operation = equal_sign + 1;
    } else {
        operation = calcul;
    }

    Token *head = lexer(operation);
    int result = 0;
    Token *current = head;
    while (current != NULL) {
        if (current->type == TOKEN_VAR) {
            current->my_token.number = get_val_variable(variables, variable_count, current->my_token.var_name);
        }
        current = current->next;
    }

    result = parser(head);

    if (variable) {
        printf("%s = %d\n", variable, result);
        set_val_variable(variables, &variable_count, variable, result);
        save(variable, result); // Sauvegarder la variable dans le fichier
        free(variable);
    } else {
        printf("Result = %d\n", result);
    }

    while (head != NULL) {
        Token *next = head->next;
        free(head);
        head = next;
    }
}
