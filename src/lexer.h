#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "types.h"

bool is_operator ( char c ) { 
    if ( c == '+' || c == '-' 
    || c == '/' || c == '*' ) {
        return true ; 
    }
    return false ; 
}

// Fonction pour vérifier si un caractère est valide pour une variable
bool is_valid_var_char(char c) {
    return (isalpha(c) || c == '_');
}

Token * add_token_number (Token * head , char num ) {
    Token * token = (Token *) malloc (sizeof(Token)); 
    token->type = NUMBER ; 
    token->my_token.number = num ; 
    token->next = NULL ; 
    if (head == NULL) {
    return token ; 
    } else {
    head->next = token ; 
    return token ; 
    }
}

Token * add_token_operator (Token * head , char op ) {
    Token * token = (Token *) malloc (sizeof(Token)); 
    token->type = OPERATOR ; 
    token->my_token.op = op ; 
    if (op == '+' || op == '-') {
        token->periorite = 1 ; 
    } else {
        token->periorite = 2 ; 
    }

    token->next = NULL ; 
    if (head == NULL) {
    return token ; 
    } else {
    head->next = token ; 
    return token ; 
    }
}

Token * add_token_var(Token * head, const char *var_name) {
    Token * token = (Token *) malloc(sizeof(Token));
    token->type = TOKEN_VAR;
    strcpy(token->my_token.var_name, var_name);
    token->next = NULL;
    if (head == NULL) {
        return token;
    } else {
        head->next = token;
        return token;
    }
}

Token * add_token_openB(Token * head, char  open) {
    Token * token = (Token *) malloc(sizeof(Token));
    token->type = OPEN_BRACKET;
    token->my_token.b_open = open ; 
    token->next = NULL;
    if (head == NULL) {
        return token;
    } else {
        head->next = token;
        return token;
    }
}

Token * add_token_closeB(Token * head, char  close) {
    Token * token = (Token *) malloc(sizeof(Token));
    token->type = CLOSE_BRACKET;
    token->my_token.b_close = close ; 
    token->next = NULL;
    if (head == NULL) {
        return token;
    } else {
        head->next = token;
        return token;
    }
}



Token * lexer ( char * operation ) {

Token * head = NULL ;
Token * tail = NULL ; 

if ( strlen(operation) == 0 ) return NULL; 
int i = 0 ; 
while (operation[i] != '\0') {
    if (operation[i] == '=' || operation[i] == ' ') {
        i ++ ; 
        continue; 
    }
    if (isdigit(operation[i])) {

    char * first_int = (char *) malloc (sizeof(char)*20); 
    first_int[0] = '\0';

    while (isdigit(operation[i])) {
    char temp[2]; 
    temp[0] = operation [i]; 
    temp[1] = '\0'; 
    strcat(first_int, temp); 
    i++; 
    }
    if (tail == NULL) {
                head = add_token_number(NULL, atoi(first_int));  
                tail = head;
            } else {
                tail = add_token_number(tail, atoi(first_int)); 
            }
    free(first_int); 
    continue; // Revenir au début du while
    }
            // Gérer les variables
        if (is_valid_var_char(operation[i])) {
            char var_name[20];
            int j = 0;

            // Extraire le nom de la variable
            while (is_valid_var_char(operation[i])) {
                var_name[j++] = operation[i++];
            }
            var_name[j] = '\0';

            // Ajouter un token de type variable
            if (tail == NULL) {
                head = add_token_var(NULL, var_name);
                tail = head;
            } else {
                tail = add_token_var(tail, var_name);
            }
            continue; // Revenir au début du while
        }

    if (is_operator(operation[i])) {
    tail = add_token_operator (tail , operation[i]);
    i++ ; 
    continue;
    } 

    if (operation[i] == '(') {  
    if (tail == NULL) {
                head =  add_token_openB (tail , operation[i]);
                tail = head;
            } else {
                tail =  add_token_openB (tail , operation[i]); 
    }
    i++ ; 
    continue;
    }

    if (operation[i] == ')') {
    tail = add_token_closeB (tail , operation[i]);
    i++ ; 
    continue;
    }
}
return head ; 
}