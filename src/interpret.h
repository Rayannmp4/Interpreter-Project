#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"

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
    token->next = NULL ; 
    if (head == NULL) {
    return token ; 
    } else {
    head->next = token ; 
    return token ; 
    }
}