#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void save(char* variable, int nb){
    //Ouverture ou création du fichier en lecture/écriture
    FILE *f = fopen("data.txt", "a+");
    if (f == NULL)
    {
        printf("Error opening file data.txt\n");
        return;
    }
    //Il faudrait faire un truc qui verifie si il y'a déjà dans le fichier et modifier le resultat si oui
    char c;
    rewind(f);
    while (c != EOF) {
        int i = 0;
        c = fgetc(f);
        while (c == variable[i]) {
            printf("car:%c position: %ld\n", c, ftell(f));
            if (variable[i + 1] == '\0') {
                long int cursor = ftell(f);
                fclose(f);
                FILE *f = fopen("data.txt", "r+");
                fseek(f, cursor+1, SEEK_SET);
                printf("position: %ld\n", ftell(f));
                fprintf(f, "%d\n", nb);

                fclose(f);
                return;
            }
            c = fgetc(f);
            i++;
        }
    }

    printf("%s sauvegardé\n", variable);
    //Quand c'est pas le cas il insère simplement la variable et le résultat à la fin du fichier
    /*Au FORMAT:
     * varOld:4
     * x:6
     *
     * */
    fputs(variable, f);
    fputc(':',f);
    fprintf(f, "%d\n", nb);

    //Fermétire sinn shaa beug
    fclose(f);
}

#ifndef SRC_SAVE_H
#define SRC_SAVE_H

#endif //SRC_SAVE_H
