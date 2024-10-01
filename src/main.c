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
    }
    return 0 ; 
}

int main () {
    char calcul[20]; 
    printf("give us an operation : "); 
    fgets(calcul , 20 , stdin); 
    printf("this %s \n", calcul); 

    char * variable = malloc(sizeof(char)*20) ;
    variable[0] = '\0'; 
    int i = 0 ; 

    while (calcul [i] != ' ' && calcul [i] != '\0') {
    char temp[2]; 
    temp[0] = calcul [i]; 
    temp[1] = '\0'; 
    strcat(variable , temp); 
    i++; 
    }
    
    
    while (calcul[i] == '=' || calcul[i] == ' ') {
    i++; 
    }

    //Token * h = NULL ; 
    //Token * t = NULL ;

    Token *token = malloc(sizeof(Token)); 
    token->type = NUMBER ; 
    token->my_token.number = calcul[i] - '0'; 
    token->next = NULL ; 
    Token *head = token ; 
    i++ ; 
    while ( calcul[i] == ' ' ) {
    i++; 
    }
    
    token->next = malloc(sizeof(Token)); 
    token->next->type = OPERATOR ; 
    token->next->my_token.op = calcul[i] ; 
    token = token->next ; 
    token->next = NULL ; 
    
    i++ ;
    while ( calcul[i] == ' ') {
    i++; 
    }
    
    token->next = malloc(sizeof(Token)); 
    token->next->type = NUMBER ; 
    token->next->my_token.number = calcul[i] - '0'; 
    token = token->next ; 
    token->next = NULL ;

    int nb = get_result(head); 

    printf("this %s = %d \n ", variable, nb); 
    free(variable); 

    while (head != NULL) {
        Token *next = head->next;
        free(head);
        head = next;
    } 
    return 0 ; 
}
