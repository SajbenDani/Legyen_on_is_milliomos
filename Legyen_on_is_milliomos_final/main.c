#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <time.h>
#include <locale.h>
#include <stdbool.h>
#include "dicsosegtabla.h"
#include "debugmalloc.h"

#ifdef _WIN32               //ez az include a magyar ékezetes szöveg importálásához kell!
#include <windows.h>
#endif


int main() {

    srand(time(NULL));

    #ifdef _WIN32                               //magyar ékezetes szöveg importálása!
        SetConsoleCP(1250);
        SetConsoleOutputCP(1250);
    #endif

    FILE *hanysor = fopen("loimbe.csv", "r");
    if (hanysor == NULL) {
        perror ("Nem tudtuk elerni a kerdesek listajat");
        return 0;
    }
    char *sor;
    sor = (char*) malloc(1000 * sizeof(char));
        if (sor == NULL){
            perror("Nem sikerült memoria helyet foglalni!!!\n");
            return 0;
        }

    char*p;
    int n = 0;
    fgets(sor,1000,hanysor);  //ez, azért van itt, mert az elso sor nem kell!
    int nehezsegtomb[15] = {0};
    while (!feof(hanysor)) {                        //1.
        fgets( sor, 1000, hanysor);
        n++;

        if(sor[1] == ';') {
            switch(sor[0]) {
                case '1':
                    nehezsegtomb[0]++;
                    break;
                case '2':
                    nehezsegtomb[1]++;
                    break;
                case '3':
                    nehezsegtomb[2]++;
                    break;
                case '4':
                    nehezsegtomb[3]++;
                    break;
                case '5':
                    nehezsegtomb[4]++;
                    break;
                case '6':
                    nehezsegtomb[5]++;
                    break;
                case '7':
                    nehezsegtomb[6]++;
                    break;
                case '8':
                    nehezsegtomb[7]++;
                    break;
                case '9':
                    nehezsegtomb[8]++;
                    break;

            }
        }else {
            switch (sor[1]) {

                case '0':
                    nehezsegtomb[9]++;
                    break;
                case '1':
                    nehezsegtomb[10]++;
                    break;
                case '2':
                    nehezsegtomb[11]++;
                    break;
                case '3':
                    nehezsegtomb[12]++;
                    break;
                case '4':
                    nehezsegtomb[13]++;
                    break;
                case '5':
                    nehezsegtomb[14]++;
                    break;
            }
        }
    }
    fclose (hanysor); // itt megszamoltuk, hogy mekkora teruletet kell foglalnunk a kerdesek tombnek!

    FILE *kerdesek = fopen("loimbe.csv", "r");
    struct Kerdessablon *excel;
    excel = (Kerdessablon*) malloc(n * sizeof(Kerdessablon));

        if (excel == NULL){
            perror("Nem sikerült memoria helyet foglalni!!!\n");
            return 0;
        }
    fgets(sor,1000,kerdesek); //ez azert van itt, mert az elso sor nem kell!

    n--;
    int hossz = 0;
    for (int i = 0; i < n; ++i){                    //2.
        fgets(sor,1000,kerdesek);
        p = strtok(sor, ";");
        excel[i].nehezseg = atoi(p);


        p = strtok(NULL, ";");
        hossz = strlen(p);
        excel[i].kerdes = (char*) malloc(sizeof(char)*hossz+1);
            if (excel[i].kerdes == NULL){
                perror("Nem sikerült memoria helyet foglalni!!!\n");
                return 0;
            }
        strcpy(excel[i].kerdes, p);
        p = strtok(NULL, ";");
        hossz = strlen(p);
        excel[i].valaszA = (char*) malloc(sizeof(char)*hossz+1);
        if (excel[i].valaszA == NULL){
            perror("Nem sikerült memoria helyet foglalni!!!\n");
            return 0;
        }
        strcpy(excel[i].valaszA, p);
        p = strtok(NULL, ";");
        hossz = strlen(p);
        excel[i].valaszB = (char*) malloc(sizeof(char)*hossz+1);
        if (excel[i].valaszB == NULL){
            perror("Nem sikerült memoria helyet foglalni!!!\n");
            return 0;
        }
        strcpy(excel[i].valaszB, p);
        p = strtok(NULL, ";");
        hossz = strlen(p);
        excel[i].valaszC = (char*) malloc(sizeof(char)*hossz+1);
        if (excel[i].valaszC == NULL){
            perror("Nem sikerült memoria helyet foglalni!!!\n");
            return 0;
        }
        strcpy(excel[i].valaszC, p);
        p = strtok(NULL, ";");
        hossz = strlen(p);
        excel[i].valaszD = (char*) malloc(sizeof(char)*hossz+1);
        if (excel[i].valaszD == NULL){
            perror("Nem sikerült memoria helyet foglalni!!!\n");
            return 0;
        }
        strcpy(excel[i].valaszD, p);
        p = strtok(NULL, ";");
        excel[i].helyes = *p;
        p = strtok(NULL, "\n");
        hossz = strlen(p);
        excel[i].kategoria = (char*) malloc(sizeof(char)*hossz+1);
        if (excel[i].kategoria == NULL){
            perror("Nem sikerült memoria helyet foglalni!!!\n");
            return 0;
        }
        strcpy(excel[i].kategoria, p);
    }

    FILE *toplista = fopen("dicsosegtabla.txt","r");
    FILE *toplista2 = fopen("dicsosegtabla.txt","r");
    kiir(toplista, toplista2);

    printf("          Szabalyok:          \n");
    printf("------------------------------\n");
    printf(" - 15 kerdes van\n - A nyeremeny kerdesenkent novekszik\n - A jatek idore megy\n - 2db segitseg elerheto(1db kozonseg segitsege es 1db felezo)\n - Felezo hasznalatahoz irja be: 'F'\n - Kozonseg segitsegehez irja be: 'K'\n");
    printf("------------------------------\n");
    printf("        Jo szorakozast!       \n\n");
    printf ("valasszon nehezesegi szintet 1-15 kozott! \n");
    int nehezseg;
    scanf ("%d", &nehezseg);
    printf("valasszon jatekos nevet! (maximum 100 karakter)\n");
    char nev[100];
    scanf ("%s", &nev);
    time_t start,end;
    start = clock();


    int nyeremenyek [16] = {0, 10000,20000,50000,100000,250000,500000,750000,1000000,1500000,2000000,5000000, 10000000,15000000,25000000, 50000000};
    int sorszam;
    int marvolt [15] = {0};
    int meddig;

    if (nehezsegtomb[nehezseg-1] <= 15){
        meddig = nehezsegtomb[nehezseg-1];
    }else {
        meddig = 15;
    }

    if (nehezsegtomb[nehezseg-1] <= 15){
        printf ("Kerdes hiany miatt, csak %d db kerdes lesz! \n", nehezsegtomb[nehezseg-1]);
    }
    FILE *dicsosegtablatemp = fopen("dicsosegtabla.temp.txt", "a");

    bool Fmarvolt = true;
    bool Kmarvolt = true;

    for (int i = 0; i <= meddig; i++) {         //3.

        LABEL1:                                                     //Itt nezzük meg, hogy ne sorsoljuk ugyan azt a számot ki kétszer
            sorszam = (rand() % nehezsegtomb[nehezseg - 1]);


            for (int k = 0; k <= 14; k++){
                if (sorszam == marvolt[k]){
                    goto LABEL1;
                }
            }
            marvolt [i] = sorszam;


            for (int j = 0; j < nehezseg-1; j++){
                sorszam += nehezsegtomb[j];
            }

            printf("%d. kerdes: \ntemakor: %s \n", i+1, excel[sorszam].kategoria);
            printf ("%s \n", excel[sorszam].kerdes);
            printf ("A valasz: %s \n", excel[sorszam].valaszA);
            printf ("B valasz: %s \n", excel[sorszam].valaszB);
            printf ("C valasz: %s \n", excel[sorszam].valaszC);
            printf ("D valasz: %s \n", excel[sorszam].valaszD);
            printf ("\n");
            printf ("Irja be a valaszat: \n");


            char valasz;
        LABEL2:
            scanf (" %c", &valasz);


            if(valasz == 'K' || valasz == 'k'){                 //kozonseg segitsege algoritmus
                int szavazatok1 = (rand() % (100 - 51 + 1)) + 51;
                int szavazatok2 = (rand() % ((100-szavazatok1) - 0 + 1)) + 0;
                int szavazatok3 = (rand() % ((100-szavazatok1-szavazatok2) - 0 + 1)) + 0;
                int szavazatok4 = (rand() % ((100-szavazatok1-szavazatok2-szavazatok3) - 0 + 1)) + 0;

                if (Kmarvolt == false){
                    printf("A felezo funkciot mar felhasznalta!\n");
                    printf ("\n");
                    printf ("Irja be a valaszat: \n");
                    goto LABEL2;

                }else {
                    Kmarvolt = false;
                    switch (excel[sorszam].helyes) {
                        case 'A':
                            printf("A valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszA, szavazatok1);
                            printf("B valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszB, szavazatok2);
                            printf("C valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszC, szavazatok3);
                            printf("D valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszD, szavazatok4);
                            printf("\n");
                            printf("Irja be a valaszat: \n");
                            goto LABEL2;
                        case 'B':
                            printf("A valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszA, szavazatok2);
                            printf("B valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszB, szavazatok1);
                            printf("C valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszC, szavazatok3);
                            printf("D valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszD, szavazatok4);
                            printf("\n");
                            printf("Irja be a valaszat: \n");
                            goto LABEL2;
                        case 'C':
                            printf("A valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszA, szavazatok3);
                            printf("B valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszB, szavazatok2);
                            printf("C valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszC, szavazatok1);
                            printf("D valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszD, szavazatok4);
                            printf("\n");
                            printf("Irja be a valaszat: \n");
                            goto LABEL2;
                        case 'D':
                            printf("A valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszA, szavazatok3);
                            printf("B valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszB, szavazatok2);
                            printf("C valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszC, szavazatok3);
                            printf("D valasz: %s      %d %% esely hogy helyes\n", excel[sorszam].valaszD, szavazatok1);
                            printf("\n");
                            printf("Irja be a valaszat: \n");
                            goto LABEL2;
                    }
                }
            }


            if (valasz == 'F' || valasz == 'f'){         //felező algoritmus
                if (Fmarvolt == false){
                    printf("A felezo funkciot mar felhasznalta!\n\n");
                    printf ("Irja be a valaszat: \n");
                    goto LABEL2;
                }else {
                    Fmarvolt = false;
                    int rosszvalasz = (rand() % 3) + 1;
                    switch (excel[sorszam].helyes) {
                        case 'A':
                            printf("A valasz: %s \n", excel[sorszam].valaszA);
                            switch (rosszvalasz) {
                                case 1:
                                    printf("B valasz: %s \n", excel[sorszam].valaszB);
                                    break;
                                case 2:
                                    printf("C valasz: %s \n", excel[sorszam].valaszC);
                                    break;
                                case 3:
                                    printf("D valasz: %s \n", excel[sorszam].valaszD);
                                    break;
                            }

                            break;
                    }
                    switch (excel[sorszam].helyes) {
                        case 'B':

                            switch (rosszvalasz) {
                                case 1:
                                    printf("A valasz: %s \n", excel[sorszam].valaszA);
                                    printf("B valasz: %s \n", excel[sorszam].valaszB);
                                    break;
                                case 2:
                                    printf("B valasz: %s \n", excel[sorszam].valaszB);
                                    printf("C valasz: %s \n", excel[sorszam].valaszC);
                                    break;
                                case 3:
                                    printf("B valasz: %s \n", excel[sorszam].valaszB);
                                    printf("D valasz: %s \n", excel[sorszam].valaszD);
                                    break;
                            }
                            break;
                    }
                    switch (excel[sorszam].helyes) {
                        case 'C':
                            switch (rosszvalasz) {
                                case 1:
                                    printf("B valasz: %s \n", excel[sorszam].valaszB);
                                    printf("C valasz: %s \n", excel[sorszam].valaszC);
                                    break;
                                case 2:
                                    printf("A valasz: %s \n", excel[sorszam].valaszA);
                                    printf("C valasz: %s \n", excel[sorszam].valaszC);
                                    break;
                                case 3:
                                    printf("C valasz: %s \n", excel[sorszam].valaszC);
                                    printf("D valasz: %s \n", excel[sorszam].valaszD);
                                    break;
                            }
                            break;
                    }
                    switch (excel[sorszam].helyes) {
                        case 'D':
                            switch (rosszvalasz) {
                                case 1:
                                    printf("B valasz: %s \n", excel[sorszam].valaszB);
                                    printf("D valasz: %s \n", excel[sorszam].valaszD);
                                    break;
                                case 2:
                                    printf("C valasz: %s \n", excel[sorszam].valaszC);
                                    printf("D valasz: %s \n", excel[sorszam].valaszD);
                                    break;
                                case 3:
                                    printf("A valasz: %s \n", excel[sorszam].valaszA);
                                    printf("D valasz: %s \n", excel[sorszam].valaszD);
                                    break;
                            }
                            break;
                    }
                    printf ("\n");
                    printf ("Irja be a valaszat: \n");
                    goto LABEL2;
                }
            }


            if (valasz == excel[sorszam].helyes || valasz == (excel[sorszam].helyes+32)){           //kis es nagy betű miatt
                if(i == meddig-1){
                    end=clock();
                    int t=(end-start)/CLOCKS_PER_SEC;
                    printf("GRATULALUNK NYERTEL!!! \n");
                    printf ("Nyeremenyed: %d Jo Magyar Forint \n", nyeremenyek[meddig]);
                    printf ("Jatekido: %d masodperc\n", t);
                    tablasorrend(nev, t, nyeremenyek[i]);
                    break;
                }else {
                    printf("Helyes valasz! \n");
                    printf("Aktualis nyeremeny: %d Jo Magyar Forint\n", nyeremenyek[i + 1]);
                }
            }
            else {
                end=clock();
                int t=(end-start)/CLOCKS_PER_SEC;
                printf ("Sajnos Kiestel! \n");
                printf("A helyes valasz: %c lett volna\n", excel[sorszam].helyes);
                printf ("Nyeremenyed: %d Jo Magyar Forint\n", nyeremenyek[i]);
                printf ("Jatekido: %d masodperc\n", t);
                tablasorrend(nev, t, nyeremenyek[i]);
                break;
            }
        }
    for (int i = 0; i < n; ++i){
        free(excel[i].kerdes);
        free(excel[i].valaszA);
        free(excel[i].valaszB);
        free(excel[i].valaszC);
        free(excel[i].valaszD);
        free(excel[i].kategoria);
    }

    fclose(hanysor);
    fclose(kerdesek);
    fclose(dicsosegtablatemp);
    free (sor);
    free(excel);
    return 0;
}
