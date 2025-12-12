#include "massiv.h"
#include <stdio.h>
#include <string.h>

int main() {
    spisok s;
    spisok_init(&s);
    
    spisok_zagruzit_iz_faila(&s, "db.txt");
    
    int choice, id, kolichestvo;
    float cena;
    char nazvanie[50];
    char filename[100] = "db.txt";
    
    while (1) {
        printf("1. Вывести все товары\n");
        printf("2. Добавить новый товар\n");
        printf("3. Удалить товар\n");
        printf("4. Поиск товара по ID\n");
        printf("5. Поиск товара по названию\n");
        printf("6. Редактировать товар\n");
        printf("7. Сохранить базу в файл\n");
        printf("8. Загрузить базу из файла\n");
        printf("9. Выход\n");
        printf("Выберите действие: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                spisok_print(&s);
                break;
                
            case 2:
                printf("Введите ID товара: ");
                scanf("%d", &id);
                printf("Введите название товара: ");
                scanf("%s", nazvanie);
                printf("Введите цену товара: ");
                scanf("%f", &cena);
                printf("Введите количество: ");
                scanf("%d", &kolichestvo);
                spisok_append(&s, id, nazvanie, cena, kolichestvo);
                break;
                
            case 3:
                printf("Введите ID товара для удаления: ");
                scanf("%d", &id);
                spisok_pop(&s, id);
                break;
                
            case 4:
                printf("Введите ID товара для поиска: ");
                scanf("%d", &id);
                spisok_poisk_id(&s, id);
                break;

            case 5:
                printf("Введите название товара для поиска: ");
                scanf("%s", nazvanie);
                spisok_poisk_nazvanie(&s, nazvanie);
                break;
                
            case 6:
                printf("Введите ID товара для редактирования: ");
                scanf("%d", &id);
                spisok_redaktirovat(&s, id);
                break;
                
            case 7:
                spisok_zapisat_v_fail(&s, filename);
                break;
                
            case 8:
                printf("Введите имя файла [db.txt]: ");
                scanf("%s", filename);
                spisok_zagruzit_iz_faila(&s, filename);
                break;
                
            case 9:
                printf("Сохранить изменения перед выходом? (1-да, 0-нет): ");
                scanf("%d", &choice);
                if (choice == 1) {
                    spisok_zapisat_v_fail(&s, "db.txt");
                }
                spisok_ochistit(&s);
                printf("Выход...\n");
                return 0;
                
            default:
                printf("Неверный выбор! Попробуйте снова.\n");
        }
    }
    
    return 0;
}