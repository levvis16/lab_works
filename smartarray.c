#include "massiv.h"

void spisok_init(spisok *s) {
    s->size = 0;
    s->head = NULL;
    s->tail = NULL;
}

void spisok_append(spisok *s, int id, char nazvanie[], float cena, int kolichestvo) {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (new_node == NULL) {
        printf("Ошибка выделения памяти!\n");
        return;
    }
    
    new_node->id = id;
    strcpy(new_node->nazvanie, nazvanie);
    new_node->cena = cena;
    new_node->kolichestvo = kolichestvo;
    new_node->next = NULL;
    
    if (s->tail == NULL) {
        s->head = new_node;
        s->tail = new_node;
    } else {
        s->tail->next = new_node;
        s->tail = new_node;
    }
    s->size++;
    printf("Товар %s добавлен в базу.\n", nazvanie);
}

int spisok_pop(spisok *s, int id) {  
    if (s->tail == NULL || s->size == 0) {
        printf("База данных пуста!\n");
        return -1;  
    }
    
    Node *current = s->head;
    Node *prev = NULL;
    
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Товар с ID %d не найден!\n", id);
        return -1;
    }
    
    if (current == s->head && current == s->tail) {
        free(current);
        s->head = NULL;
        s->tail = NULL;
    } else if (current == s->head) {
        s->head = current->next;
        free(current);
    } else if (current == s->tail) {
        prev->next = NULL;
        s->tail = prev;
        free(current);
    } else {
        prev->next = current->next;
        free(current);
    }
    
    s->size--;
    printf("Товар с ID %d удален.\n", id);
    return 0;
}

void spisok_print(spisok *s) {
    Node *current = s->head;
    
    if (s->size == 0) {
        printf("База данных пуста!\n");
        return;
    }
    
    printf("Всего товаров: %d\n\n", s->size);
    printf("ID  Название\t\tЦена\tКоличество\n");
    
    while (current != NULL) {
        printf("%-4d %-20s %-8.2f %-8d\n", 
               current->id, current->nazvanie, current->cena, current->kolichestvo);
        current = current->next;
    }
}

Node* spisok_poisk_id(spisok *s, int id) {
    Node *current = s->head;
    int pos = 1;
    
    while (current != NULL) {
        if (current->id == id) {
            printf("Товар найден (позиция %d):\n", pos);
            printf("ID: %d, Название: %s, Цена: %.2f, Количество: %d\n", 
                   current->id, current->nazvanie, current->cena, current->kolichestvo);
            return current;
        }
        current = current->next;
        pos++;
    }
    
    printf("Товар с ID %d не найден\n", id);
    return NULL;
}

Node* spisok_poisk_nazvanie(spisok *s, char nazvanie[]) {
    Node *current = s->head;
    int pos = 1;
    int found = 0;
    
    printf("Результаты поиска по названию '%s':\n", nazvanie);
    while (current != NULL) {
        if (strstr(current->nazvanie, nazvanie) != NULL) {
            printf("%d. ID: %d, Название: %s, Цена: %.2f, Количество: %d\n", 
                   pos, current->id, current->nazvanie, current->cena, current->kolichestvo);
            found = 1;
        }
        current = current->next;
        pos++;
    }
    
    if (!found) {
        printf("Товары с названием '%s' не найдены\n", nazvanie);
        return NULL;
    }
    return NULL;
}

void spisok_redaktirovat(spisok *s, int id) {
    Node *tovar = spisok_poisk_id(s, id);
    
    if (tovar == NULL) {
        return;
    }
    
    printf("\nРедактирование товара:\n");
    
    char new_nazvanie[50];
    float new_cena;
    int new_kolichestvo;
    
    printf("Новое название [%s]: ", tovar->nazvanie);
    scanf("%s", new_nazvanie);
    
    printf("Новая цена [%.2f]: ", tovar->cena);
    scanf("%f", &new_cena);
    
    printf("Новое количество [%d]: ", tovar->kolichestvo);
    scanf("%d", &new_kolichestvo);
    
    strcpy(tovar->nazvanie, new_nazvanie);
    tovar->cena = new_cena;
    tovar->kolichestvo = new_kolichestvo;
    
    printf("Товар отредактирован!\n");
}

int spisok_zapisat_v_fail(spisok *s, char filename[]) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Ошибка открытия файла для записи!\n");
        return -1;
    }
    
    Node *current = s->head;
    while (current != NULL) {
        fprintf(file, "%d %s %.2f %d\n", 
                current->id, current->nazvanie, current->cena, current->kolichestvo);
        current = current->next;
    }
    
    fclose(file);
    printf("База данных сохранена в текстовый файл %s\n", filename);
    return 0;
}

int spisok_zagruzit_iz_faila(spisok *s, char filename[]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Файл %s не найден. Создана новая база данных.\n", filename);
        return -1;
    }
    
    spisok_ochistit(s);
    
    int id, kolichestvo;
    float cena;
    char nazvanie[50];
    
    while (fscanf(file, "%d %s %f %d", &id, nazvanie, &cena, &kolichestvo) == 4) {
        spisok_append(s, id, nazvanie, cena, kolichestvo);
    }
    
    fclose(file);
    printf("База данных загружена из текстового файла %s\n", filename);
    return 0;
}

void spisok_ochistit(spisok *s) {
    Node *current = s->head;
    Node *next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    s->head = NULL;
    s->tail = NULL;
    s->size = 0;
}