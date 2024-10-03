#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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

    // créer le token de int 1
    Token *head = add_token_number (NULL , calcul[i]); 
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
    
    // ajouter le token de int 2
    tail = add_token_number (tail , calcul[i]);
    
    // calculer 
    int nb = get_result(head); 

    // afficher le resultat 
    printf("this %s = %d \n ", variable, nb); 
    free(variable); 
    
    // free des malloc 
    while (head != NULL) {
        Token *next = head->next;
        free(head);
        head = next;
    } 
    return 0 ; 
}
>>>>>>> 4b07deb7a03c5ee8e9a3a0ba491ba6d5468cd8da
