#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>

#include "readMap.h"
#include "writeMap.h"
#include "solver.h"
#include "list.h"

/*
  ** SODOKU SOLVER
  **
  ** A program készítője: Pallag Jonatán
  **
  ** A program célja: a felhasználó megadhat (fájlból, konzolból) egy sodoku-t,
  ** válaszul a sodoku-t megoldja a program (akár ezt le is vezeti, ha úgy kér),
  ** és egy beolvasott/beöltött sodoku pályát el is menthet más néven
*/

/**
 * Event leírja az egyes eseményeket: megnyitás, betöltése, megoldás, kiíratás, mentés, segítség, kilépés, nincs esemény
 */
typedef enum Event {Open, Load, Solve, Print, Save, Help, Exit, NoEvent} Event;

/**
 * Megadja egy adott szövegről, hogy melyik eseményhez tartozó utasítás
 * @param s az utasítás
 * @return az utasításhoz tartozó esemény enumja
 */
Event getEvent(char * s);

/**
 * A megnyitáshoz tartozó eseményt írja le
 * @param map a sodoku pálya
 */
void ev_open (List * map[9][9]);

/**
 * A a sodoku pálya betöltését kezeli
 * @param map a sodoku pálya
 */
void ev_load (List * map[9][9]);

/**
 * A sodoku-t oldja meg (a szabványos bemenetről eldönti, hogy kell-e levezetni a megoldást)
 * @param map a sodoku pálya
 */
void ev_solve(List * map[9][9]);

/**
 * Kiíírja a sodoku pályát a konzolba
 * @param map a sodoku pálya
 */
void ev_print(List * map[9][9]);

/**
 * Egy fájlba elmenti a pályát
 * @param map a sodoku pálya
 */
void ev_save (List * map[9][9]);

/**
 * HELP - súgó, ami informálja a felhasználót az egyes parancsokról
 */
void help();

/**
 * A program fő része, mely kezeli az egyes utasításokat
 * @return visszajelzést ad, hogy sikeresen zárult-e le a program lefutása
 */
int main (void) {
    List * map[9][9] = {{NULL}};
    char s[100];

    //Menü
    while(scanf(" %s", s) == 1) {

        system("cls");
        Event ev = getEvent(s);

        switch(ev) {
        case Open:
            ev_open (map);
            break;
        case Load:
            ev_load (map);
            break;
        case Solve:
            ev_solve(map);
            break;
        case Print:
            ev_print(map);
            break;
        case Save:
            ev_save (map);
            break;
        case Help:
            help();
            break;
        case Exit:
            clearMap(map);
            exit(0);
        case NoEvent:
            continue;
        }
    }

    clearMap(map);
    return 0;
}

Event getEvent(char * s) {
    if(!strcmp(s, "load" )) return Load;
    if(!strcmp(s, "open" )) return Open;
    if(!strcmp(s, "solve")) return Solve;
    if(!strcmp(s, "print")) return Print;
    if(!strcmp(s, "save" )) return Save;
    if(!strcmp(s, "help" )) return Help;
    if(!strcmp(s, "exit" )) return Exit;
    return NoEvent;
}

void ev_open(List * map[9][9]) {
    clearMap(map);
    char s[100];

    if(scanf("%s", s) != 1) {
        printf("Wrong scan!\n");
        return;
    }

    system("cls");
    scanfMapFromFile(map, s);
}

void ev_load(List * map[9][9]) {
    clearMap(map);
    scanfMapFromConsol(map);
}

void ev_solve(List * map[9][9]) {
    if(isMap(map)) {
        printf("Do you want see the solution? 0 = no, 1 = true \n");
        char answer;
        if(scanf(" %c", &answer) == 1) {
            //Sodoku megoldása
            solveSodoku(map, answer != '0');
        }
    } else {
        //A pálya nincs betöltve
        printf("Please load a sodoku!\n");
    }
}

void ev_print(List * map[9][9]) {
    if(isMap(map)) {
        //A pálya be van töltve
        printfMap(map);
    } else {
        //A pálya nincs betöltve
        printf("Please load a sodoku!\n");
    }
}

void ev_save(List * map[9][9]) {
    //Ha még nincs betöltött sodoku
    if(!isMap(map)) {
        printf("Please load a sodoku!\n");
        return;
    }

    //Fájl nevének beolvasása a consolból
    char s[100];
    if(scanf("%s", s) == 1) {
        printfMapFile(map, s);
        system("cls");
        printf("The sodoku  saved!\n\n");
    } else {
        printf("Invalid scan!\n");
    }
}

void help() {
    printf("HELP:"
           " \tload <map> - load a sodoku map from consol                                                   \n"
           " \topen <path> - open a sodoku map from file (the file containts <map> text)                    \n"
           " \tsave <path> - save opened sodoku                                                             \n"
           " \tsolve - solve the opened sodoku                                                              \n"
           " \tprint - print the opened sodoku                                                              \n"
           " \texit - exit                                                                                \n\n"
           "<map> examples: \n\t040 080 070                                                                 \n"
           " \t200 004 050                                                                                  \n"
           " \t700 009 604                                                                                \n\n"
           " \t374 000 800                                                                                  \n"
           " \t000 836 000                                                                                  \n"
           " \t006 000 935                                                                                \n\n"
           " \t102 300 007                                                                                  \n"
           " \t090 400 006                                                                                  \n"
           " \t060 010 020                                                                                \n\n"
           "or:\t.4..8..7.2....4.5.7....96.4374...8.....836.....6...9351.23....7.9.4....6.6..1..2.\netc.  \n\n"
           "NOTICE:                                                                                         \n"
           "   0 = '.' = '_'\t- it means all possible number 1-9 (other character don't matter!)            \n");
}
