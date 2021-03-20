#include <stdio.h>

#include "writeMap.h"
#include "list.h"

//Kiír n-szer egy c-karaktert a konozolra
void printfChars(int n, char c) {
    for(int i = 0; i<n; i++) {
        printf("%c", c);
    }
}

//Kiírja a lista elemeit (speciális módon)
void List_print(List *list) {
    printf(" ");
    bool zip = false;   //Ha több egymást követõ szám van, akkor egyszerûsít (1,2,3 helyett 1-3)
    int last = 0;
    while(1 <= List_getSize(list)) {
        int n = 1;
        if(3 <= List_getSize(list) && List_getValue(list, 0) + 1 == List_getValue(list, 1) && List_getValue(list, 1) + 1 == List_getValue(list, 2)) {
            if(!zip) {
                last = List_getValue(list, 0);
                zip = true;
            }
        } else if (zip) {
            if(last == 1 && List_getValue(list, 1) == 9) printf("_");
            else printf("%d-%d", last, List_getValue(list, 1));
            if(List_getSize(list) > 2) printf(";");
            zip = false;
            n++;
        } else {
            printf("%d", List_getValue(list, 0));
            if(List_getSize(list) > 1) printf(";");
        }
        list = List_get(list, n);
    }
    printf(" ");
}

//Kiszámolja, hogy milyen hosszú lenne a kiírt lista
int List_getPrintedSize(List *list) {
    int db = 2;
    bool zip = false;   //Ha több egymást követõ szám van, akkor egyszerûsít (1,2,3 helyett 1-3)
    int last = 0;
    while(1 <= List_getSize(list)) {
        int n = 1;
        if(3 <= List_getSize(list) && List_getValue(list, 0) + 1 == List_getValue(list, 1) && List_getValue(list, 1) + 1 == List_getValue(list, 2)) {
            if(!zip) {
                last = List_getValue(list, 0);
                zip = true;
            }
        } else if (zip) {
            if(last == 1 && List_getValue(list, 1) == 9) db++;
            else db+=3;
            if(List_getSize(list) > 2) db++;
            zip = false;
            n++;
        } else {
            db++;
            if(List_getSize(list) > 1) db++;
        }
        list = List_get(list, n);
    }
    return db;
}

//PÁLYA KIÍRÁSA
//Consolba
void printfMap(List * map[9][9]) {
    int lengths [9] = {0};
    int szumlengths = 0;
    for(int j=0; j<9; j++) {
        for(int i=0; i<9; i++) {
            int size = List_getPrintedSize(map[i][j]);
            if(size>lengths[j]) {
                lengths[j] = size;
            }
        }
        szumlengths +=lengths[j];
    }
    for(int i=0; i<9; i++) {
        if(i%3 == 0) {
            printfChars(szumlengths+4, '*');
            printf("\n");
        }
        for(int j=0; j<9; j++) {
            if(j%3 == 0)
                printf("*");
            List_print(map[i][j]);
            printfChars(lengths[j] - List_getPrintedSize(map[i][j]), ' ');
        }
        printf("*\n");
    }
    printfChars(szumlengths+4, '*');
    printf("\n");
}

//Fájlba
void printfMapFile(List * map[9][9], char * src) {
    FILE * f = fopen(src, "w");
    if(f == NULL){
        printf("Wrong path!");
        return;
    }
    for(int i = 0; i<9; i++) {
        for(int j = 0; j<9; j++) {
            char s[3];
            s[0] = (List_getSize(map[i][j]) == 9) ? '.' : '0' + map[i][j]->x;
            if((j+1)%3 == 0) {
                s[1] = ' ';
                s[2] = '\0';
            } else {
                s[1] = '\0';
            }
            fprintf(f, "%s", s);
        }
        fprintf(f, "\n");
        if((i+1)%3 == 0) fprintf(f, "\n");
    }
    fclose(f);
    return;
}
