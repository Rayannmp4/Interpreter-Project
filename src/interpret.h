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
            printf("Retrieved value for %s: %d\n", name, variables[i].value);  // Message de débogage
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

char * get_condition (const char * input ) {
    const char* open_bracket = strchr (input, '(');
    const char* close_bracket = strchr (input, ')');

    if (!open_bracket || !close_bracket || open_bracket > close_bracket ) {
        printf("Syntaxe Invalide, des parenthese manquantes !"); 
        return NULL; 
    }

    size_t condition_length = close_bracket - open_bracket ; 
    char * condition = (char*)malloc(condition_length + 1);
    strncpy(condition, open_bracket +1, condition_length - 1);
    condition[condition_length] = '\0';
    return condition ; 
}


char * get_block_content (const char * input) {

    char * start = strchr(input, '{');
    char* end = strchr(input, '}');

    if ( !start || !end || start > end ) {
        printf("Syntaxe Invalide, des accolades manquantes !");
        return NULL; 
    }

    size_t block_length = end - start - 1 ; 
    char * block = (char*)malloc(block_length + 1);

    if (block == NULL) {
        perror("Allocation error");
        exit(EXIT_FAILURE);
    }

    strncpy(block, start + 1, block_length);
    block[block_length] = '\0';

    return block; 
}

Comp_type get_comp_type(const char *comp_str) {

    if (strcmp(comp_str, "<") == 0) return INF;
    if (strcmp(comp_str, ">") == 0) return SUP;
    if (strcmp(comp_str, "==") == 0) return EGA;
    if (strcmp(comp_str, "!=") == 0) return DIFF;
    if (strcmp(comp_str, ">=") == 0) return SUP_EGA;
    if (strcmp(comp_str, "<=") == 0) return INF_EGA;

    printf("Error: invalid comparator '%s'\n", comp_str);
    exit(EXIT_FAILURE); 
}

Condition * create_condition (char * input) {
    Condition* cond = (Condition*)malloc(sizeof(Condition));

    if (cond == NULL) {
        printf("Error: memory allocation failed !\n");
        exit(EXIT_FAILURE);
    }

    char var[20], comp[3];
    int value; 

    if (sscanf(input, "%19s %2s %d", var, comp, &value) != 3) {
        printf("Error: invalid condition format '%s'\n", input);
        exit(EXIT_FAILURE);
    }
    
    cond->var = strdup(var); 
    cond->comp = get_comp_type(comp);
    cond->value = value;

    return cond;
}

bool evaluate_condition(const Condition *cond, int current_value) {
    switch (cond->comp) {
        case INF:
            return current_value < cond->value;
        case SUP:
            return current_value > cond->value;
        case EGA:
            return current_value == cond->value;
        case DIFF:
            return current_value != cond->value;
        case SUP_EGA:
            return current_value >= cond->value;
        case INF_EGA:
            return current_value <= cond->value;
        default:
            printf("Error: invalid comparator in condition\n");
            exit(EXIT_FAILURE);
    }
}

int get_value (const char* variable) {

    FILE *f = fopen("data.txt", "r");
    if (f == NULL) {
        printf("Error opening file data.txt\n");
        exit(EXIT_FAILURE);
    }

    char file_var[20];
    int value; 
    bool found = false;

    while (fscanf(f, "%19[^:]:%d\n", file_var, &value) == 2) {
        if (strcmp(file_var, variable) == 0) {
            found = true;
            break;
        }
    }

    fclose(f);

    if (!found) {
        printf("Variable '%s' not initialized.\n", variable);
        exit(EXIT_FAILURE);
    } else {
        return value ; 
    }
    
}

void interpret(const char* input, bool isBoucle) {
    
    // si c'est une boucle 
    Condition * condition; 
    if (isBoucle) {
        char * conditionChar = get_condition(input); 
    // récuperer le block d'instructions du while
    if ( conditionChar != NULL ) { 
        condition = create_condition(conditionChar); 
        input = get_block_content(input); 
    }
    }
  
    // Créez une copie modifiable de `input`
    char *modifiable_input = strdup(input);  // Copie modifiable de `input`

    if (strncmp(modifiable_input, "print(", 6) == 0 && modifiable_input[strlen(modifiable_input) - 1] == ')') {
        modifiable_input[strlen(modifiable_input) - 1] = '\0';  // Supprime la parenthèse fermante
        char *variable = modifiable_input + 6;  // Pointeur vers le nom de la variable
        read(variable);
        printf("\n");
        free(modifiable_input);  // Libère la copie avant de retourner
        return;
    }

    char calcul[50];
    strcpy(calcul, modifiable_input);  // Copie modifiable_input dans calcul

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

    // Tokenization de l'opération
    Token *head = lexer(operation);

    if (isBoucle && condition) {
    // first call
    // Remplacer les variables par leurs valeurs
    Token *current = head;
    while (current != NULL) {
        if (current->type == TOKEN_VAR) {
            printf("we got into condition \n"); 
            // Remplace le nom de la variable par sa valeur
            current->my_token.number = get_val_variable(variables, variable_count, current->my_token.var_name);
            printf("Replaced variable %s with value %d\n", current->my_token.var_name, current->my_token.number);  // Débogage
            current->type = NUMBER;  // Change le type en NUMBER pour l'évaluation
        }
        current = current->next;
    }

    int result = parser(head); 
    set_val_variable(variables, &variable_count, variable, result);
    int val = get_val_variable(variables, variable_count, variable); 
    
    while(evaluate_condition(condition, val )) {
    // Remplacer les variables par leurs valeurs
        result = parser(head);

        set_val_variable(variables, &variable_count, variable, result);
        val = get_val_variable(variables, variable_count, variable);
        printf("Loop iteration: %s = %d, Condition: %d\n", condition->var, val, evaluate_condition(condition, val)); 
    }
    printf("%s = %d\n", variable, result);
    free(variable);
    free(condition);
    } else {
     // Remplacer les variables par leurs valeurs
    Token *current = head;
    while (current != NULL) {
        if (current->type == TOKEN_VAR) {
            // Remplace le nom de la variable par sa valeur
            current->my_token.number = get_val_variable(variables, variable_count, current->my_token.var_name);
            printf("Replaced variable %s with value %d\n", current->my_token.var_name, current->my_token.number);  // Débogage
            current->type = NUMBER;  // Change le type en NUMBER pour l'évaluation
        }
        current = current->next;
    }

    // Évaluer l'expression
    int result = parser(head);
    if (variable) {
        printf("%s = %d\n", variable, result);
        set_val_variable(variables, &variable_count, variable, result);
        free(variable);
    } else {
        printf("Result = %d\n", result);
    }
    }
    // Libération des tokens
    while (head != NULL) {
        Token *next = head->next;
        free(head);
        head = next;
    }

    free(modifiable_input);  // Libère la copie de `input` après utilisation
}
