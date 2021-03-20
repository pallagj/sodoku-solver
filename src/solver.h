#ifndef SOLVER_H_INCLUDED
#define SOLVER_H_INCLUDED

/**
 * Felszabadítja a map mátrixban (sodoku pálya) található listákat
 * @param map az a mátrix (sodoku pálya) amiben található az egyes lehetőségeket szimbolizáló listák
 */
void clearMap(List * map[9][9]);

/**
 * Megmondja egy adott sodokuról, hogy ténylegesen mindenhol vannak lehetőségek, vagy fix elemek
 * @param map a bemeneti sodoku mátrix
 * @return igaz, amennyiben nincs benne üres elem, azaz minden elemében van 1 vagy annál több lehetőség
 */
bool isMap(List * map[9][9]);

/**
 * Sodoku megoldó
 * @param map bemeneti sodoku pálya
 * @param with_solution megadja, hogy kell levezetni a megoldást (igaz), vagy egyszerűen a megoldásokat írja ki (hamis)
 */
void solveSodoku(List * map[9][9], bool with_solution);


#endif // SOLVER_H_INCLUDED
