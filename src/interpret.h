#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"
#include "read.h"
#include "lexer.h"
#include "parser.h"

Variable variables[100];
int variable_count = 0;

int get_val_variable(Variable *variables, int count, const char* name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    printf("Error!!! Variable '%s' not found. Value is 0.\n", name);
    return 0;
}

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
    save(name, value);  // Sauvegarde de la variable
}

void interpret(const char* input) {
    // Vérifiez si la commande est un "print(...)"
    if (strncmp(input, "print(", 6) == 0 && input[strlen(input) - 1] == ')') {
        char variable[20];
        strncpy(variable, input + 6, strlen(input) - 7);
        variable[strlen(input) - 7] = '\0';  // Terminer la chaîne
        read(variable);  // Lire et afficher la valeur de la variable
        printf("\n");
        return;
    }

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
    int result = parser(head);

    if (variable) {
        printf("%s = %d\n", variable, result);
        set_val_variable(variables, &variable_count, variable, result);
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
