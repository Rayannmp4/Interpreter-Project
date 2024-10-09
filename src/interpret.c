#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"
#include "interpret.h"

int get_result(Token *temp) {

    int result = 0 ;
    char op = '+';
    // int a = temp->my_token.number;
    // temp = temp->next;
    
    while (temp != NULL) {

        if (temp == NULL || temp->type != NUMBER) {
            printf("Erreur de syntaxe\n");
            return -1;
        }

        // int b = temp->my_token.number;
    if(temp->type == NUMBER){
        switch (op) {
            case '+': 
                result += temp->my_token.number; 
                break;
            case '-': 
                result -= temp->my_token.number;  
                break;
            case '*':
                result *= temp->my_token.number;  
                break;
            case '/':
                if (temp->my_token.number != 0) {
                    result /= temp->my_token.number;  
                } else {
                    printf("Division par zero.\n");
                    return -1;  
                }
                break;

            case '%': 
                if (temp->my_token.number != 0) {
                    result %= temp->my_token.number;
                } else {
                    printf("Modulo zero\n");
                    return -1;
                }
                break;
            default:
                printf("Operateur pas pris en charge\n");
                return -1;
        }
    } else if (temp->type == OPERATOR) {
            op = temp->my_token.op;
    }
        temp = temp->next;
    }

    return result;
}

Token * add_token_number (Token * head , char num ) {
    Token * token = (Token *) malloc (sizeof(Token)); 

    if (token == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }
    token->type = NUMBER ; 
    token->my_token.number = num - '0'; 
    token->next = NULL ; 
    if (head == NULL) {
    return token ; 
    } else {
        head->next = token ; 
        return token ; 
    }
}

Token * add_token_operator(Token * head, char op) {
    Token * token = (Token *) malloc (sizeof(Token));

    if (token == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        return NULL;
    }

    token->type = OPERATOR;
    
    // Vérifie si c'est un opérateur valide
    if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%') {
        token->my_token.op = op;
    } else {
        printf("Opérateur non pris en charge : %c\n", op);
        free(token);
        return NULL;
    }

    token->next = NULL;
    
    if (head != NULL) {
        head->next = token;
    }

    return token;
}