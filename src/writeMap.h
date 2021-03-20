#ifndef WRITEMAP_H_INCLUDED
#define WRITEMAP_H_INCLUDED

#include "list.h"

//PÁLYA KIÍRÁSA
/**
 * Kiír egy listákból álló mátrixból a konzolba
 * @param map az a mátrix, aminek ki kell írni az egyes elemeit, mindig az összes lehetőséget kiírja (ha mind a 9 lehetséges, akkor '_'-jelet)
 */
void printfMap(List * map[9][9]);

/**
 * Kiír egy listákból álló mátrixból a fájlba
 * @param map az a mátrix, aminek ki kell írni az egyes elemeit, fix elem estén az adott értéket, egyéb esetben pedig '.'-t
 */
void printfMapFile(List * map[9][9], char * src) ;

#endif // WRITEMAP_H_INCLUDED
