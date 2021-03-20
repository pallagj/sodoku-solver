#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdarg.h>
#include "List.h"

//LISTÁVAL A MÛVELETEK

//A listához hozzáfûz egy újabb elemet az utolsó helyre
void List_add(List ** list0, int x) {
    if(*list0 == NULL) {
        *list0 = malloc(sizeof(List));
        (*list0)->x = x;
        (*list0)->next = NULL;
        return;
    }
    List * list = *list0;
    //Utolsó elem megkeresése
    while(list->next!=NULL) list = list->next;

    //Elem hozzáadása
    list->next = malloc(sizeof(List));
    list->next->x = x;
    list->next->next = NULL;
}

//Listából lekér egy elemet az index szerint
List *List_get(List *list, int I) {
    //Megkeressük az I-edik elemet
    for(int i = 1; i <= I; i++) {
        if(list==NULL) return NULL;
        list = list->next;
    }

    return list;
}

//Listából lekér egy eleme értékét az index szerint
int List_getValue(List *list, int I) {
    //Megkeressük az I-edik elemet
    for(int i = 1; i <= I; i++) {
        if(list==NULL) return -1;
        list = list->next;
    }

    return list->x;
}

//Listából lekéri az első eleme értékét
int Lis_getFirstValue(List *list) {
    return list->x;
}

//Listából lekéri az utolsó eleme értékét
int Lis_getLastValue(List *list) {

    while(list->next != NULL) {
        list = list->next;
    }

    return list->x;
}

//Listából lekéri az utolsó elemet
List *Lis_getLast(List *list) {

    while(list->next != NULL) {
        list = list->next;
    }

    return list;
}

//Listából kitöröl egy elemet, igaz érték, ha törölt
bool List_removeElement(List **list_original, int x) {
    List * list = *list_original;
    //Elsõ elem vajon jó-e?
    if(list == NULL) return false;
    //Ha az első elemet kell törölni
    if(list->x == x) {

        if(list->next == NULL) //Ha csak egy elemű a lista
            *list_original = NULL;
        else //Több elem esetén
            *list_original = list->next;

        free(list);
        return true;
    }

    //1. utáni elemek
    while(list->next!=NULL && list->next->x != x)
        list = list->next;

    //Nem talált, akkor kilép
    if(list->next == NULL) return false;

    //Megtalált elem kitörlése
    List * value = list->next;
    list->next = list->next->next;
    free(value);
    return true;
}

//Egyedi lista létrehozása
List *List_createList(int n, ...) {
    if(n==0) return NULL;

    //Lista feltöltése
    va_list valist;
    va_start(valist, n);

    List *list = NULL;

    for(int i = 0; i<n; i++)
        List_add(&list, va_arg(valist, int));

    va_end(valist);
    return list;
}

//Visszaadja a lista méretét
int List_getSize(List *list) {
    int n = 0;
    while(list!=NULL) {
        list = list->next;
        n++;
    }
    return n;
}

//Visszaadja a másolt listát
List * List_clone(List * list) {
    if(list == NULL) return NULL;

    List * list_clone  = malloc(sizeof(List));
    List * list_cloned = list_clone;

    while(list->next != NULL) {
        list_clone->x = list->x;
        list_clone->next = malloc(sizeof(List));

        list_clone = list_clone->next;
        list       = list      ->next;
    }

    list_clone->x    = list->x;
    list_clone->next = NULL;

    return list_cloned;
}

//Kitörli a listát
void List_clear(List ** list_original) {
    List * list = *list_original;
    while(list != NULL) {
        List * next= list->next;
        free(list);
        list = next;

    }
    *list_original = NULL;
}

//Kitöröli az összes felsorolt listát
void Lists_clear(int n, ...) {
    va_list valist;
    va_start(valist, n);

    for(int i=0; i<n; i++) {
        List ** list = va_arg(valist, List**);
        List_clear(list);
    }

    va_end(valist);
}
