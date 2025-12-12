#ifndef MASSIV_H  
#define MASSIV_H  

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int id;
    char nazvanie[50];
    float cena;
    int kolichestvo;
    struct Node *next;
} Node;

typedef struct spisok {
    int size;
    Node *head;
    Node *tail;
} spisok;

void spisok_init(spisok *s);
void spisok_append(spisok *s, int id, char nazvanie[], float cena, int kolichestvo);
int spisok_pop(spisok *s, int id);        
void spisok_print(spisok *s);
Node* spisok_poisk_id(spisok *s, int id);
Node* spisok_poisk_nazvanie(spisok *s, char nazvanie[]);
void spisok_redaktirovat(spisok *s, int id);
int spisok_zapisat_v_fail(spisok *s, char filename[]);
int spisok_zagruzit_iz_faila(spisok *s, char filename[]);
void spisok_ochistit(spisok *s);

#endif