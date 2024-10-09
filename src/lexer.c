#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "types.h"

Token *tokeniser(char *expr){
    Token *head = NULL ;
    Token *current = NULL ;

    while (*expr != '\0')
    {
        // on va ignorer les espaces
        if (*expr == ' ')
        {
            expr++;
            continue;
        }

        Token *newToken = malloc(sizeof(Token));

        if (newToken == NULL)
        {
            printf("Erreur d'allocation\n");
            return NULL;
        }
        
        //vérifie si c'est un nombre/chiffre 
        if (*expr >= '0' && *expr <= '9')   
        {

            int number = 0;
            while (*expr >= '0' && *expr <= '9') {
                number = number * 10 + (*expr - '0');  
                expr++;  
            }

            newToken->type = NUMBER ;
            newToken->my_token.number = number ;
        } else {
            newToken->type = OPERATOR;
            newToken->my_token.op = *expr;
        }
        
        newToken->next = NULL;
        if (head == NULL) {
            head = newToken;
        } else {
            current->next = newToken;
        }
        current = newToken;
    }

    return head;
    
} 