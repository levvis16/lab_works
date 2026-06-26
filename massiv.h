#ifndef MASSIV_H
#define MASSIV_H

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>  // Для исключений

struct Product {
    int id;
    std::string nazvanie;
    float cena;
    int kolichestvo;
    
    friend std::ostream& operator<<(std::ostream& os, const Product& p);
    friend std::istream& operator>>(std::istream& is, Product& p);
};

class Spisok {
private:
    Product* data;
    int size;
    int capacity;
    
    void resize();

public:
    Spisok();
    ~Spisok();
    
    void append(int id, const std::string& nazvanie, float cena, int kolichestvo);
    bool pop(int id);
    void print() const;
    
    // Изменяем возвращаемый тип на константную ссылку
    const Product& poisk_id(int id) const;
    const Product& poisk_nazvanie(const std::string& nazvanie) const;
    
    void redaktirovat(int id);
    bool zapisat_v_fail(const std::string& filename) const;
    bool zagruzit_iz_faila(const std::string& filename);
    void ochistit();
};

#endif