#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//La variable désigne l'entrée du terminal. Elle est sous le format print(...)

void read(char* variable){
    //Ouverture ou création du fichier en lecture/écriture
    FILE *f = fopen("data.txt", "a+");
    if (f == NULL)
    {
        printf("Error opening file data.txt\n");
        return;
    }
    char c;
    rewind(f);
    //Parcourir le fichier
    while (c != EOF){
        //initialisation à 6 car la commande est "print(..."
        //                                              ^ 6eme indexe
        int i = 6;
        //recuperation et decalage du curseur jusqu'a ce que c égal la premiere lettre de la variable
        c = fgetc(f);
        //Cette boucle permet de vérifier que la ligne contient la chaîne 'variable'
        while (c == variable[i]){
            //Parceque print(...) ce termine par ')'
            if(variable[i+1] == ')'){
                /*On décale à droite car si on cherche 'x' FORMAT DU FICHIER:
                 * variablotin:4
                 * variablotron:4
                 * x:3
                 *  ^
                 * */
                fseek(f, 1, SEEK_CUR);
                int n;
                fscanf(f, "%d", &n);
                //Affichage de l'entier
                printf("%d", n);
                return;
            }
            //Charactères suivants
            c = fgetc(f);
            i++;
        }

    }
    //Fermétire sinn shaa beug
    fclose(f);

}

#ifndef SRC_READ_H
#define SRC_READ_H

#endif //SRC_READ_H
