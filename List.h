#ifndef LIST
#define LIST

#include <stdbool.h>

/**
 * Egész számokat tartalmazó lista definiálása struktúrával
 *
 * @param x:     egy egész szám, mely egy lehetőség a sodoku játék egy cellájában
 * @param *next: következő lista elemre mutató pointer
 *
 **/
typedef struct List {
    int x;
    struct List *next;
} List;

//LISTÁVAL A MÛVELETEK

/**
 * A listához hozzáfûz egy újabb elemet az utolsó helyre
 * @param list a listára mutató pointer
 * @param x    egy új szám, amit a listához kell adni
 */
void List_add(List ** list, int x) ;

/**
 * Listából lekér egy elemet az index szerint
 * @param list a lista elejére mutató pointer
 * @param I    az adott index
 *
 * @return visszaadja az adott indexű elemre mutató pointert
 */
List *List_get(List *list, int I) ;

/**
 * Listából lekér egy elem értékét az index szerint
 * @param list a lista elejére mutató pointer
 * @param I    az adott index
 *
 * @return visszaadja az adott indexű elem értékét
 */
int List_getValue(List *list, int I) ;

/**
 * Listából lekéri az első elem értékét
 * @param list a lista elejére mutató pointer
 *
 * @return lista első elemének értéke
 */
int Lis_getFirstValue(List *list) ;

/**
 * Listából lekéri az utolsó elem értékét
 * @param list a lista elejére mutató pointer
 *
 * @return lista utolsó elemének értéke
 */
int Lis_getLastValue(List *list) ;

//Listából lekéri az utolsó elemet

/**
 * Listából lekéri az utolsó elemet
 * @param list a lista elejére mutató pointer
 *
 * @return lista utolsó elemére mutató pointer
 */
List *Lis_getLast(List *list) ;

/**
 * Listából kitöröl egy elemet
 * @param list_original a listára mutató pointer (itt teljes kitörléskor szükséges lehet a NULL-ra állítás, azért **)
 * @param x megadja, hogy melyik értéket kell kivenni a listából (csak egyet vesz ki)
 * @return igaz - ha sikerült törölni
 */
bool List_removeElement(List **list_original, int x);

/**
 * Egyedi lista létrehozása
 * @param n hány elemű legyen a lista
 * @param ... az egyes elemek érétéket kell felsorolni (n db)
 * @return visszatér a létrehozott lista elejével
 */
List *List_createList(int n, ...);

/**
 * Visszaadja a lista méretét
 * @param list lista eleje
 * @return lista hossza
 */
int List_getSize(List *list) ;

/**
 * Egy listát klónoz, és a klónozott listával tér vissza
 * @param list lista (elejét kell átadni), amit klónozni kell
 * @return a klónozott lista
 */
List * List_clone(List * list) ;

/**
 * Kitörli a listát (felszabadítja a memóriában foglalt területet)
 * @param list_original listára mutató pointer
 */
void List_clear(List ** list_original) ;

/**
 * Kitöröli az összes felsorolt listát
 * @param n a törlendő listák száma
 * @param ... törlendő listákra mutató pointerek felsorolása
 */
void Lists_clear(int n, ...) ;

#endif // LIST
