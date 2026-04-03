#include "massiv.h"

int main() {
    Spisok s;
    s.zagruzit_iz_faila("db.txt");
    
    int choice, id, kolichestvo;
    float cena;
    std::string nazvanie;
    std::string filename = "db.txt";
    
    while (true) {
        std::cout << "\n1. Вывести все товары\n";
        std::cout << "2. Добавить новый товар\n";
        std::cout << "3. Удалить товар\n";
        std::cout << "4. Поиск товара по ID\n";
        std::cout << "5. Поиск товара по названию\n";
        std::cout << "6. Редактировать товар\n";
        std::cout << "7. Сохранить базу в файл\n";
        std::cout << "8. Загрузить базу из файла\n";
        std::cout << "9. Выход\n";
        std::cout << "Выберите действие: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1:
                s.print();
                break;
            case 2:
                std::cout << "Введите ID: "; std::cin >> id;
                std::cout << "Введите название: "; std::cin >> nazvanie;
                std::cout << "Введите цену: "; std::cin >> cena;
                std::cout << "Введите количество: "; std::cin >> kolichestvo;
                s.append(id, nazvanie, cena, kolichestvo);
                break;
            case 3:
                std::cout << "Введите ID: "; std::cin >> id;
                s.pop(id);
                break;
            case 4:
                std::cout << "Введите ID: "; std::cin >> id;
                s.poisk_id(id);
                break;
            case 5:
                std::cout << "Введите название: "; std::cin >> nazvanie;
                s.poisk_nazvanie(nazvanie);
                break;
            case 6:
                std::cout << "Введите ID: "; std::cin >> id;
                s.redaktirovat(id);
                break;
            case 7:
                s.zapisat_v_fail(filename);
                break;
            case 8:
                std::cout << "Введите имя файла [db.txt]: "; std::cin >> filename;
                s.zagruzit_iz_faila(filename);
                break;
            case 9:
                std::cout << "Сохранить изменения? (1-да, 0-нет): "; std::cin >> choice;
                if (choice == 1) s.zapisat_v_fail("db.txt");
                std::cout << "Выход...\n";
                return 0;
            default:
                std::cout << "Неверный выбор!\n";
        }
    }
}