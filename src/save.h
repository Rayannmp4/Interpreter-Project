#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void save(char* variable, int nb){
    FILE *f = fopen("data.txt", "a+");
    if (f == NULL)
    {
        printf("Error opening file data.txt\n");
        return;
    }
    fputs(variable, f);
    fputc(':',f);
    fprintf(f, "%d\n", nb);

    /*fprintf(f, "%d", nb);
    fseek(f, 1, SEEK_SET);
    printf("\n%ld", ftell(f));

    int n;
    fscanf(f, "%d", &n);
    printf("\nres = %d", n);*/

}

#ifndef SRC_SAVE_H
#define SRC_SAVE_H

#endif //SRC_SAVE_H
