#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "dicsosegtabla.h"
#include "debugmalloc.h"



void tablasorrend(char nev[100], int ido, int nyeremeny){
    FILE *filebeir = fopen("dicsosegtabla.txt", "a");
    if (filebeir == NULL) {
        perror ("Nem tudtuk elerni a dicsosegtablat!\n");
        return;
    }
    fprintf(filebeir, "%s; %d; %d\n",nev, ido, nyeremeny);
    fclose(filebeir);

    char *sor;
    sor = (char*) malloc(1000 * sizeof(char));
    if (sor == NULL){
        perror("Nem sikerült memoria helyet foglalni!!!\n");
        return;
    }

    FILE *file = fopen("dicsosegtabla.txt", "r");
    if (file == NULL) {
        perror ("Nem tudtuk elerni a dicsosegtablat!\n");
        return;
    }

    int osszjatekos = 0;
    while(fgets(sor,1000,file) != NULL){
        osszjatekos++;
    }
    fclose(file);

    Tabledesign *tomb;
    tomb = (Tabledesign*) malloc(osszjatekos * sizeof(Tabledesign));
    if (tomb == NULL){
        perror("Nem sikerült memoria helyet foglalni!!!\n");
        return;
    }

    char *p1;
    FILE *file2 = fopen("dicsosegtabla.txt", "r");
    if (file2 == NULL) {
        perror ("Nem tudtuk elerni a dicsosegtablat!\n");
        return;
    }
    for(int i = 0; i < osszjatekos; i++){
        fgets(sor,1000,file2);

        p1 = strtok(sor, ";");
        strcpy(tomb[i].nev, p1);

        p1 = strtok(NULL, ";");
        tomb[i].ido = atoi(p1);

        p1 = strtok(NULL, "\n");
        tomb[i].nyeremeny = atoi(p1);
    }
    fclose(file2);

    for (int i = osszjatekos-1; i > 0; --i) {

        for (int j = 0; j < i; ++j) {
            if (tomb[j].nyeremeny < tomb[j + 1].nyeremeny) {
                Tabledesign temp = tomb[j];
                tomb[j] = tomb[j + 1];
                tomb[j + 1] = temp;
            } else {
                if (tomb[j].nyeremeny == tomb[j + 1].nyeremeny) {
                    if (tomb[j].ido > tomb[j + 1].ido) {
                        Tabledesign temp = tomb[j];
                        tomb[j] = tomb[j + 1];
                        tomb[j + 1] = temp;
                    }
                }
                }
            }
    }

    FILE *filesorba = fopen("dicsosegtabla.txt", "w");
    if (filesorba == NULL) {
        perror ("Nem tudtuk elerni a dicsosegtablat!\n");
        return;
    }
    for (int i = 0; i < osszjatekos; i++){
        fprintf(filesorba, "%s; %d; %d\n",tomb[i].nev, tomb[i].ido, tomb[i].nyeremeny);
    }

    fclose(filesorba);
    free(tomb);
    free(sor);

}
