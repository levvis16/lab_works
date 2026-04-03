#include "massiv.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << p.id << " " << p.nazvanie << " " << p.cena << " " << p.kolichestvo;
    return os;
}

std::istream& operator>>(std::istream& is, Product& p) {
    is >> p.id >> p.nazvanie >> p.cena >> p.kolichestvo;
    return is;
}

Spisok::Spisok() : size(0), capacity(10) {
    data = new Product[capacity];
}

Spisok::~Spisok() {
    delete[] data;
}

void Spisok::resize() {
    capacity *= 2;
    Product* new_data = new Product[capacity];
    for (int i = 0; i < size; i++) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
}

void Spisok::append(int id, const std::string& nazvanie, float cena, int kolichestvo) {
    if (size >= capacity) {
        resize();
    }
    data[size].id = id;
    data[size].nazvanie = nazvanie;
    data[size].cena = cena;
    data[size].kolichestvo = kolichestvo;
    size++;
    std::cout << "Товар " << nazvanie << " добавлен в базу.\n";
}

bool Spisok::pop(int id) {
    for (int i = 0; i < size; i++) {
        if (data[i].id == id) {
            for (int j = i; j < size - 1; j++) {
                data[j] = data[j + 1];
            }
            size--;
            std::cout << "Товар с ID " << id << " удален.\n";
            return true;
        }
    }
    std::cout << "Товар с ID " << id << " не найден!\n";
    return false;
}

void Spisok::print() const {
    if (size == 0) {
        std::cout << "База данных пуста!\n";
        return;
    }
    
    std::cout << "Всего товаров: " << size << "\n\n";
    std::cout << std::left << std::setw(4) << "ID" 
              << std::setw(20) << "Название"
              << std::setw(8) << "Цена" 
              << std::setw(8) << "Кол-во" << "\n";
    
    for (int i = 0; i < size; i++) {
        std::cout << std::left << std::setw(4) << data[i].id
                  << std::setw(20) << data[i].nazvanie
                  << std::setw(8) << data[i].cena
                  << std::setw(8) << data[i].kolichestvo << "\n";
    }
}

Product* Spisok::poisk_id(int id) const {
    for (int i = 0; i < size; i++) {
        if (data[i].id == id) {
            std::cout << "Товар найден:\n";
            std::cout << "ID: " << data[i].id 
                      << ", Название: " << data[i].nazvanie
                      << ", Цена: " << data[i].cena 
                      << ", Количество: " << data[i].kolichestvo << "\n";
            return &data[i];
        }
    }
    std::cout << "Товар с ID " << id << " не найден\n";
    return nullptr;
}

Product* Spisok::poisk_nazvanie(const std::string& nazvanie) const {
    bool found = false;
    for (int i = 0; i < size; i++) {
        if (data[i].nazvanie.find(nazvanie) != std::string::npos) {
            std::cout << "ID: " << data[i].id 
                      << ", Название: " << data[i].nazvanie
                      << ", Цена: " << data[i].cena 
                      << ", Количество: " << data[i].kolichestvo << "\n";
            found = true;
        }
    }
    if (!found) {
        std::cout << "Товары с названием '" << nazvanie << "' не найдены\n";
        return nullptr;
    }
    return nullptr;
}

void Spisok::redaktirovat(int id) {
    Product* p = poisk_id(id);
    if (p == nullptr) return;
    
    std::string new_nazvanie;
    float new_cena;
    int new_kolichestvo;
    
    std::cout << "Новое название [" << p->nazvanie << "]: ";
    std::cin >> new_nazvanie;
    std::cout << "Новая цена [" << p->cena << "]: ";
    std::cin >> new_cena;
    std::cout << "Новое количество [" << p->kolichestvo << "]: ";
    std::cin >> new_kolichestvo;
    
    p->nazvanie = new_nazvanie;
    p->cena = new_cena;
    p->kolichestvo = new_kolichestvo;
    
    std::cout << "Товар отредактирован!\n";
}

bool Spisok::zapisat_v_fail(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Ошибка открытия файла для записи!\n";
        return false;
    }
    
    for (int i = 0; i < size; i++) {
        file << data[i] << "\n";
    }
    
    file.close();
    std::cout << "База данных сохранена в файл " << filename << "\n";
    return true;
}

bool Spisok::zagruzit_iz_faila(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Файл " << filename << " не найден. Создана новая база данных.\n";
        return false;
    }
    
    ochistit();
    
    Product p;
    while (file >> p) {
        append(p.id, p.nazvanie, p.cena, p.kolichestvo);
    }
    
    file.close();
    std::cout << "База данных загружена из файла " << filename << "\n";
    return true;
}

void Spisok::ochistit() {
    delete[] data;
    size = 0;
    capacity = 10;
    data = new Product[capacity];
}