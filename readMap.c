#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "readMap.h"

//PÁLYA BEOLVASÁSA
//Consolból
void scanfMapFromConsol(List * map[9][9]) {
    printf("Adja meg a sodoku palyajat!\n");
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
            char a;
            scanf("%c", &a);

            //Egyéb karakter esetén figyelmen kívül hagyja a lépést
            if(!(('0' <= a && a <= '9') || (a == '.' || a == '_' ))) {
                j--;
                continue;
            }

            if(a == '.' || a == '_' ) a = '0';

            a -= '0';

            if(a==0) {
                map[i][j] = List_createList(9, 1,2,3,4,5,6,7,8,9);
            } else {
                map[i][j] = List_createList(1, a);
            }
        }
    }

    //Jelzés a felhasználónak a betöltés sikeréről
    system("cls");
    printf("The sodoku loaded!\n\n");
}

//Fájlból
void scanfMapFromFile(List * map[9][9], char * src) {
    FILE * f;
    f = fopen(src, "r");
    if(f == NULL) {
        system("cls");
        printf("File does not exist!\n");
        return;
    }
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {

            char a = 0;
            if(fscanf(f, "%c", &a)<1) {

                //Nem sikerült beolvasni a fájlt :(
                system("cls");
                printf("Wrong file!\n");

                //Fel kell szabadítani a beolvasott listákat
                for(int i1 = 0; i1 < i; i1++) {
                    for(int j1 = 0; j1 < j; j1++) {
                        List_clear(&map[i1][j1]);
                    }
                }
                return;
            }

            //Egyéb karakter esetén figyelmen kívül hagyja a lépést
            if(!(('0' <= a && a <= '9') || (a == '.' || a == '_' ))) {
                j--;
                continue;
            }

            if(a == '.' || a == '_' ) a = '0';

            a -= '0';

            if(a == 0) {
                map[i][j] = List_createList(9, 1,2,3,4,5,6,7,8,9);
            } else {
                map[i][j] = List_createList(1, a);
            }
        }
    }
    fclose(f);
    printf("The sodoku is opened!\n");
}
