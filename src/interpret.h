#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "types.h"

int get_result( Token * temp ) {
    int a = temp->my_token.number ; 
    temp = temp->next; 
    char op = temp->my_token.op ; 
    temp = temp->next ; 
    int b = temp->my_token.number; 
    switch (op) {
        case '+' : 
        return a + b ; 
        break;
        case '-' : 
        return a - b ;
        break; 
        case '/' : 
        if (b != 0) {
        return a / b ;
        }
        break;
        case '%' : 
        if (a >= b) {
            return a%b ; 
        } 
        break;     
        default : 
        return -1 ;    
    }
    return -1 ; 
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