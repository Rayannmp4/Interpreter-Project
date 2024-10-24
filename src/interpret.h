#ifndef INTERPRET_H
#define INTERPRET_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "lexer.h"

void get_result( Token * temp ,int * result) {
    if ( temp == NULL || temp -> next == NULL) {
    return ; 
    }

    // operateur 
    char op = temp->my_token.op ; 
    // deuxieme entier 
    temp = temp->next ; 
    int b = temp->my_token.number; 

    switch (op) {
        case '+' : 
        *result = *result + b ; 
        break;
        case '-' : 
        *result = *result - b ;
        break; 
        case '/' : 
        if (b != 0) {
        *result = *result / b ;
        }
        break;
        case '*' : 
        *result = *result * b ; 
        break;     
        default : 
        *result = -1 ;    
        return ; 
    }
    
    if (temp->next != NULL) {
        get_result(temp->next , result);
    } 
}

char * get_variable (char * calcul ) {
     // initialiser le nom de la variable à 'vide'
    char * variable = malloc(sizeof(char)*20) ;
    variable[0] = '\0'; 
    int i = 0 ; 
   
    while (calcul[i] == '=' || calcul[i] == ' ') {
    i++; 
    }

    // parcourir jusqu'au premier espace
    while (calcul [i] != ' ' && calcul [i] != '\0') {
    char temp[2]; 
    temp[0] = calcul [i]; 
    temp[1] = '\0'; 
    strcat(variable , temp); 
    i++; 
    }
}

Token * add_token_operator (Token * head , char op ) {
    Token * token = (Token *) malloc (sizeof(Token)); 
    token->type = OPERATOR ; 
    token->my_token.op = op ; 
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
