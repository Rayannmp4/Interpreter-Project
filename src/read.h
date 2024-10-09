#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void read(char* variable){
    FILE *f = fopen("data.txt", "a+");
    if (f == NULL)
    {
        printf("Error opening file data.txt\n");
        return;
    }
    char c;
    rewind(f);
    while (c != EOF){
        int i = 0;
        c = fgetc(f);
        while (c == variable[i+6]){
            if(variable[i+7] == '\0'){
                fseek(f, 1, SEEK_CUR);
                int n;
                fscanf(f, "%d", &n);
                printf("\nres = %d", n);
            }
            i++;
        }
    }

    /*fprintf(f, "%d", nb);
    fseek(f, 1, SEEK_SET);
    printf("\n%ld", ftell(f));

    int n;
    fscanf(f, "%d", &n);
    printf("\nres = %d", n);*/

}

#ifndef SRC_READ_H
#define SRC_READ_H

#endif //SRC_READ_H
