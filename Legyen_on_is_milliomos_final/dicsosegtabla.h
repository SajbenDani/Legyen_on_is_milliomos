//
// Created by sajbe on 2022. 11. 05..
//

#ifndef LEGYEN_ON_IS_MILLIOMOS_FINAL_DICSOSEGTABLA_H
#define LEGYEN_ON_IS_MILLIOMOS_FINAL_DICSOSEGTABLA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "debugmalloc.h"

typedef struct Kerdessablon {
    int nehezseg;
    char *kerdes;
    char *valaszA;
    char *valaszB;
    char *valaszC;
    char *valaszD;
    char helyes;
    char *kategoria;

} Kerdessablon;


typedef struct Tabledesign {
    char nev[100];
    int ido;
    int nyeremeny;
} Tabledesign;

void tablasorrend(char nev[100], int ido, int nyeremeny);
void kiir(FILE *file, FILE *file2);
#endif //LEGYEN_ON_IS_MILLIOMOS_FINAL_DICSOSEGTABLA_H


