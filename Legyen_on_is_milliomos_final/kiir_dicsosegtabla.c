//
// Created by sajbe on 2022. 11. 23..
//

#include "dicsosegtabla.h"
#include "debugmalloc.h"

void kiir(FILE *file, FILE *file2){
    char *sor;
    sor = (char*) malloc(1000 * sizeof(char));
        if (sor == NULL){
           perror("Nem sikerült memoria helyet foglalni!!!\n");
            return;
        }

    int osszjatekos = 0;
    while(fgets(sor,1000,file) != NULL){
        osszjatekos++;
    }
    fclose(file);

    printf("          TOP LISTA:          \n");
    printf("------------------------------\n");

    if(osszjatekos > 10){
        osszjatekos = 10;
    }

    for (int i = 1; i <= osszjatekos; ++i) {
        fgets(sor, 1000, file2);
        printf("TOP %d: %s \n", i, sor);
    }
    printf ("------------------------------\n\n\n");
    free(sor);
    fclose(file2);
}