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
            printf("Retrieved value for %s: %d\n", name, variables[i].value); 
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
    save(name, value);  
}

void interpret(const char* input) { 
    // Créez une copie modifiable de `input`
    char *modifiable_input = strdup(input);

    if (strncmp(modifiable_input, "print(", 6) == 0 && modifiable_input[strlen(modifiable_input) - 1] == ')') {
        modifiable_input[strlen(modifiable_input) - 1] = '\0';  // Supprime la parenthèse fermante
        char *variable = modifiable_input + 6;  // Pointeur vers le nom de la variable
        read(variable);
        printf("\n");
        free(modifiable_input);  
        return;
    }

    char calcul[50];
    strcpy(calcul, modifiable_input);  

    char *equal_sign = strstr(calcul, "=");
    char *operation = NULL;
    char *variable = NULL;

    if (equal_sign) {
        variable = malloc(sizeof(char) * 20);

    if (variable == NULL) {
            printf("Error: memory allocation failed !\n");
            exit(EXIT_FAILURE);
    }
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

    // Tokenization de l'opération
    Token *head = lexer(operation);

    
    Token *current = head;
    while (current != NULL) {
        if (current->type == TOKEN_VAR) {
            
            current->my_token.number = get_val_variable(variables, variable_count, current->my_token.var_name);
            printf("Replaced variable %s with value %d\n", current->my_token.var_name, current->my_token.number);  
            current->type = NUMBER;  
        }
        current = current->next;
    }

    int result = parser(head);

    if (variable) {
        printf("%s = %d\n", variable, result);
        set_val_variable(variables, &variable_count, variable, result);
        free(variable);
    } else {
        printf("Result = %d\n", result);
    }

    // Libération des tokens
    while (head != NULL) {
        Token *next = head->next;
        free(head);
        head = next;
    }

    free(modifiable_input);  
}
