#include <stdio.h>
#include <stdlib.h>

#include "List.h"
#include "writeMap.h"

//Kitörli a map-et
void clearMap(List * map[9][9]) {
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
            List_clear(&map[i][j]);
        }
    }
}

bool isMap(List * map[9][9]) {
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
            if(map[i][j] == NULL) return false;
        }
    }
    return true;
}


bool cellSimplifyFast(List * map[9][9], bool first, int i, int j, int r) {
    int list_size;
    bool removed;

    //Amennyiben nem az elsp elem, akkor az indexek szerint megadott elem listájából ki kell szedni az r lehetőséget
    if(!first) {
        removed   = List_removeElement(&map[i][j], r);
        list_size = List_getSize(map[i][j]);
        if (list_size == 0) return true;
    }

    //Ha egy elemre csökkent, vagy az első meghívásról van szó
    if(first || (removed && list_size == 1)) {
        //Végig kell nézni a megadott indexek szerinti elemhez tartozó további elemeket, majd egyszerűsíteni velkük
        for(int k = 0; k<9; k++) {

            //SOR
            if(k!=i && cellSimplifyFast(map, false, k, j, map[i][j]->x)) return true;

            //OSZLOP
            if(k!=j && cellSimplifyFast(map, false, i, k, map[i][j]->x)) return true;

            //NAGYOBB CELLA
            int I = i/3*3 + k/3;
            int J = j/3*3 + k%3;
            if((I!=i||J!=j) && cellSimplifyFast(map, false, I, J, map[i][j]->x)) return true;
        }
    }
    return false;
}

//Egy adott cellában kiveszi a felesleges lehetõségeket, de úgy, hogy végignézi az összes oszlop/sor/nagyobb celláihoz
void cellSimplify(List * map[9][9], int i, int j) {

    //Kiindulási listaméret
    int start_n = List_getSize(map[i][j]);
    if(start_n == 1) return;

    //A már nem lehetséges elemek kivétele az aktuális cellából
    for(int k = 0; k<9; k++) {
        //Sor szerint
        if(k!=j && (List_getSize(map[i][k]) == 1))
            if(List_removeElement(&map[i][j], map[i][k]->x) && List_getSize(map[i][j]) == 1) break;

        //Oszlop szerint
        if(k!=i && List_getSize(map[k][j]) == 1)
            if(List_removeElement(&map[i][j], map[k][j]->x) && List_getSize(map[i][j]) == 1) break;

        //Nagyobb cella egység szerint
        int I = i/3*3 + k/3, J = j/3*3 + k%3;
        if(!(i==I && j==J) && List_getSize(map[I][J]) == 1)
            if(List_removeElement(&map[i][j], map[I][J]->x) && List_getSize(map[i][j]) == 1) break;
    }

    //Végső lehetőség méret
    int end_n = List_getSize(map[i][j]);

    //Igaz érték, ha az aktuális cella egy elemű lett
    if(start_n > 1 && end_n == 1) {
        cellSimplifyFast(map, true, i, j, 0);
    }
}

//Megajda, hogy van valahol 1-nél több lehetőség (igaz, ha van)
bool checkUnique(List * map[9][9]) {
    //Sor oszlop ellenőrzése
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
            if(List_getSize(map[i][j]) > 1) {
                return false;
            }
        }
    }
    return true;
}

//Helyes-e a megoldás?
bool check(List * map[9][9]) {
    //Sor oszlop ellenőrzése
    for(int i = 0; i<9; i++) {

        //Az ellenőrzéshez a 3 lista létrehozása
        List * list0 = List_createList(9, 1,2,3,4,5,6,7,8,9);
        List * list1 = List_createList(9, 1,2,3,4,5,6,7,8,9);
        List * list2 = List_createList(9, 1,2,3,4,5,6,7,8,9);

        //Az egyes lehetőségek
        for(int k = 0; k<9; k++) {
            if(map[k][i] == NULL || map[i][k] == NULL ||map[i/3*3+k/3][i%3*3 + k%3] == NULL) {
                Lists_clear(3, &list0, &list1, &list2);
                return false;
            }

            //Lehetőségek kitörlése
            List_removeElement(&list0, map[k][i]->x);
            List_removeElement(&list1, map[i][k]->x);
            List_removeElement(&list2, map[i/3*3+k/3][i%3*3 + k%3]->x);
        }

        //Ellenőrzés
        if(list0 != NULL || list1 != NULL || list2 != NULL) {
            Lists_clear(3, &list0, &list1, &list2);
            return false;
        }

        //Felszabadítás
        Lists_clear(3, &list0, &list1, &list2);
    }
    return true;
}

/*
    Ez a két változó csupán a statisztikára szolgál
    cntr_sol:  számolja, hogy hány megoldás történik a megoldás során
    cntr_cntr: számolja, hogy hány ellentmondásba ütközik a megoldó
*/
int cntr_cntr = 0, cntr_sol = 0;

//Sodoku megoldó
void solve(List * map[9][9], bool for_one, int I, int J, bool with_solution) {

    //Ha le kell vezetni a megoldást
    if(with_solution) {
        if(!for_one) {
            //Kiindulási sodoku
            printf("The started sodoku:\n\n");
            printfMap(map);
            printf("\n");
        } else {
            //Sodoku pályák megoldás közben
            if(!checkUnique(map)) {
                printfMap(map);
                printf("\n");
            } else if(!check(map)) {
                printf("Wrong case selection!\n");
            }
        }
    }

    //A tábla maximális leegyszerűsítése
    if(for_one) {
        if(cellSimplifyFast(map, true, I, J, 0)) {
            if(with_solution) printf("CONTRADICTION!\n\n");
            cntr_cntr++;
            clearMap(map);
            return;
        }
    } else {
        for(int i = 0; i<9; i++) {
            for(int j = 0; j<9; j++) {
                cellSimplify(map, i, j);
            }
        }
    }
    if(with_solution) {
        printf("Simplified sodoku:\n\n");
        printfMap(map);
        printf("\n");
    }

    //Ha ezek után maradt lehetőség, akkor a legkevesebb esetnél bontsuk szét lehetőségekre
    int min_i, min_j, min_size;

    bool first = true;
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
            int list_size = List_getSize(map[i][j]);
            if(1 < list_size && (first || list_size < min_size)) {
                min_size = list_size;
                min_i = i;
                min_j = j;

                first = false;
            }
        }
    }

    //Ha van esetválasztás
    if(!first) {
        if(with_solution) printf("Case selection (%d. row, %d. column)\n\n", min_i+1, min_j+1, with_solution);
        //Első lehetőség
        for(int k = 0; k < min_size; k++) {
            if(with_solution) printf("- At %d:\n", List_getValue(map[min_i][min_j], k));
            //A pálya klónozása
            List * mapclone[9][9];
            for(int i = 0; i < 9; i++) {
                for(int j = 0; j < 9; j++) {
                    if(min_i != i || min_j != j) mapclone[i][j] = List_clone(map[i][j]);
                }
            }

            //A pálya legekvesebb (>1) lehetőséget tartalmazó cellájának az eseteinek a szétbontása:
            List * cloned = malloc(sizeof(List));
            cloned-> x = List_get(map[min_i][min_j], k)->x;
            cloned->next = NULL;
            mapclone[min_i][min_j] = cloned;

            //Az adott esetre a függvény újrameghívása
            solve(mapclone, true, min_i, min_j, with_solution);
        }
    }

    //Talált helyes megoldást
    if(check(map)&&first) {

        if(with_solution) {
            printf("IT WAS A GOOD SOLUTION!\n\n");
        } else {
            printf("SOLUTION:\n\n");
            printfMapFile(map, "solved.txt");
            printfMap(map);
            printf("\n");
        }

        //Megoldások számának növelése
        cntr_sol++;
    }

    clearMap(map);

    //Statisztika
    if(!for_one) {
        printf("The number of solutions:\t%d\n", cntr_sol);
        printf("The number of contradictions:\t%d\n", cntr_cntr);
        cntr_cntr = 0;
        cntr_sol  = 0;
    }

    return;
}

void solveSodoku(List * map[9][9], bool with_solution) {

    //A klónozott sodoku-t kell megoldani
    List * map_clone[9][9] = {{NULL}};
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            map_clone[i][j] = List_clone(map[i][j]);
        }
    }

    //Megoldás, és azok kiírása
    solve(map_clone, false, 0, 0, with_solution);
}
