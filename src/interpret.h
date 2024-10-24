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
    return variable ;
}

void interpret (char * calcul) {
    // valeur d'entrée temp
    //char calcul[50]; 
    //printf("give us an operation : "); 
    //fgets(calcul , 50 , stdin); 
    //printf("this %s \n", calcul); 
    Token * head = lexer(calcul);
    char * variable = get_variable(calcul);
    // calculer 
    int result = head->my_token.number ; 
    get_result(head->next , &result); 

    // afficher le resultat 
    printf("this %s = %d \n", variable, result); 
    free(variable); 

    
    // free des malloc 
    while (head != NULL) {
        Token *next = head->next;
        free(head);

        head = next;
    } 
}

#endif 