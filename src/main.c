#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "types.h"
#include "lexer.h"
#include "save.h"
#include "read.h"

int main () {
    while (true) {
    // valeur d'entrée temp
    char calcul[50]; 
    printf("give us an operation : "); 
    fgets(calcul , 50 , stdin);
    char* print = "print(";
    int v = 1;
    for(int i = 0; i < 6; i++){
        if(calcul[i] != print[i]){
            v = 0;
        }
    }
    if(v == 1){
        read(calcul);
        return 1;
    }
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

    Token *head = get_operation_list (calcul); 
    
    // calculer 
    int result = head->my_token.number ; 
    get_result(head->next , &result);

    save(variable,result);

    // afficher le resultat 
    printf("this %s = %d \n", variable, result); 
    free(variable); 

    
    // free des malloc 
    while (head != NULL) {
        Token *next = head->next;
        free(head);

        head = next;
    }
    }    return 0 ;
}
