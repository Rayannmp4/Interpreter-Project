#ifndef LEXER_H
#define LEXER_H
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
    }
    if (is_operator(operation[i])) {
    tail = add_token_operator (tail , operation[i]);
    }
    i++ ; 
}
return head ; 
}

#endif 