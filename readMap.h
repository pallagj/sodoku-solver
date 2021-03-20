#ifndef READMAP_H_INCLUDED
#define READMAP_H_INCLUDED

#include "List.h"

/**
 * Beolvas egy listákból álló mátrixba a konzolból
 * @param map az a mátrix, amibe kell beolvasni a sodoku elemeit, amennyiben '.', '_', '0',
 * karaktereket talál, akkor azokat úgy tekinti, hogy ott ismeretlen található, azaz mind a 9 lehetőséggel tölti fel,
 * ezektől és az 1-9 karakterektől eltérőektől eltekint a beolvasás során
*/
void scanfMapFromConsol(List * map[9][9]);

/**
 * Beolvas egy listákból álló mátrixba egy szöveges állományt
 * @param map az a mátrix, amibe kell beolvasni a sodoku elemeit, amennyiben '.', '_', '0',
 * karaktereket talál, akkor azokat úgy tekinti, hogy ott ismeretlen található, azaz mind a 9 lehetőséggel tölti fel,
 * ezektől és az 1-9 karakterektől eltérőektől eltekint a beolvasás során
*/
void scanfMapFromFile(List * map[9][9], char * src);


#endif // READMAP_H_INCLUDED
