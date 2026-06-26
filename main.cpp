#include "massiv.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string filename;
    
    if (argc > 1) {
        filename = argv[1];
        std::cout << "Загружаем базу из файла: " << filename << "\n";
    } else {
        std::cout << "Введите имя файла базы данных (по умолчанию db.txt): ";
        std::getline(std::cin, filename);
        if (filename.empty()) {
            filename = "db.txt";
        }
    }
    
    Spisok s;
    s.zagruzit_iz_faila(filename);
    
    int choice, id, kolichestvo;
    float cena;
    std::string nazvanie;
    
    while (true) {
        std::cout << "\n=== База данных: " << filename << " ===\n";
        std::cout << "1. Вывести все товары\n";
        std::cout << "2. Добавить новый товар\n";
        std::cout << "3. Удалить товар\n";
        std::cout << "4. Поиск товара по ID\n";
        std::cout << "5. Поиск товара по названию\n";
        std::cout << "6. Редактировать товар\n";
        std::cout << "7. Сохранить базу в файл\n";
        std::cout << "8. Загрузить базу из другого файла\n";
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
                try {
                    const Product& found = s.poisk_id(id);
                    std::cout << "Товар найден:\n";
                    std::cout << "ID: " << found.id 
                              << ", Название: " << found.nazvanie
                              << ", Цена: " << found.cena 
                              << ", Количество: " << found.kolichestvo << "\n";
                } catch (const std::runtime_error& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            case 5:
                std::cout << "Введите название: "; std::cin >> nazvanie;
                try {
                    const Product& found = s.poisk_nazvanie(nazvanie);
                    std::cout << "Товар найден:\n";
                    std::cout << "ID: " << found.id 
                              << ", Название: " << found.nazvanie
                              << ", Цена: " << found.cena 
                              << ", Количество: " << found.kolichestvo << "\n";
                } catch (const std::runtime_error& e) {
                    std::cout << e.what() << "\n";
                }
                break;
            case 6:
                std::cout << "Введите ID: "; std::cin >> id;
                s.redaktirovat(id);
                break;
            case 7:
                s.zapisat_v_fail(filename);
                break;
            case 8: {
                std::string new_filename;
                std::cout << "Введите имя файла для загрузки: ";
                std::cin >> new_filename;
                s.zagruzit_iz_faila(new_filename);
                filename = new_filename;
                break;
            }
            case 9:
                std::cout << "Сохранить изменения? (1-да, 0-нет): "; 
                int save;
                std::cin >> save;
                if (save == 1) s.zapisat_v_fail(filename);
                std::cout << "Выход...\n";
                return 0;
            default:
                std::cout << "Неверный выбор!\n";
        }
    }
}