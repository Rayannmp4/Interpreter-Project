#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "interpret.h"

int main () {
    // valeur d'entrée temp
    char calcul[20]; 
    printf("give us an operation : "); 
    fgets(calcul , 20 , stdin); 
    printf("this %s \n", calcul); 

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
    
    // ignorer les espaces 
    while (calcul[i] == '=' || calcul[i] == ' ') {
    i++; 
    }
    
    char * first_int = malloc (sizeof(char)*20); 
    first_int[0] = '\0';

    while (isdigit(calcul[i])) {
    char temp[2]; 
    temp[0] = calcul [i]; 
    temp[1] = '\0'; 
    strcat(first_int, temp); 
    i++; 
    }

    // créer le token de int 1
    Token *head = add_token_number (NULL , atoi(first_int)); 
    Token * tail = head ; 

    // ignorer les espaces 
    i++ ; 
    while ( calcul[i] == ' ' || calcul[i] == '=') {
    i++; 
    }
    
    // ajouter le token de int 2
    tail = add_token_operator (tail , calcul[i]); 

    // ignorer les espaces 
    i++ ;
    while ( calcul[i] == ' ') {
    i++; 
    }

    char * second_int = malloc (sizeof(char)*20); 
    second_int[0] = '\0';

    while (isdigit(calcul[i])) {
    char temp[2]; 
    temp[0] = calcul [i]; 
    temp[1] = '\0'; 
    strcat(second_int, temp); 
    i++; 
    }
    
    // ajouter le token de int 2
    tail = add_token_number (tail , atoi(second_int));
    
    // calculer 
    int nb = get_result(head); 

    // afficher le resultat 
    printf("this %s = %d \n ", variable, nb); 
    free(variable); 
    free(first_int); 
    
    // free des malloc 
    while (head != NULL) {
        Token *next = head->next;
        free(head);
        head = next;
    } 
    return 0 ; 
}
