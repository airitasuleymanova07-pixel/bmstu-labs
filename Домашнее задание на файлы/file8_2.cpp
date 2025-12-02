#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <locale.h>
#include <iomanip>

using namespace std;

struct Product {
    int id;
    string name;
    string category;
    double price;
    int quantity;
};

int main() {
    setlocale(LC_ALL, "rus");

    ifstream csvFile("products.csv");

    if (!csvFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл products.csv" << endl;
        return 1;
    }

    vector<Product> products;
    string line;
    getline(csvFile, line);

    while (getline(csvFile, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 5) {
            Product p;
            p.id = stoi(tokens[0]);
            p.name = tokens[1];
            p.category = tokens[2];
            p.price = stod(tokens[3]);
            p.quantity = stoi(tokens[4]);
            products.push_back(p);
        }
    }

    csvFile.close();

    int choice;
    cout << "Выберите критерий фильтрации:" << endl;
    cout << "1. Товары дороже 5000 рублей" << endl;
    cout << "2. Товары из категории 'Электроника'" << endl;
    cout << "3. Товары с количеством больше 10" << endl;
    cout << "4. Товары дешевле 1000 рублей" << endl;
    cout << "Введите номер: ";
    cin >> choice;

    vector<Product> filteredProducts;

    switch (choice) {
    case 1: {
        auto expensive_filter = [](const Product& p) { return p.price > 5000; };
        copy_if(products.begin(), products.end(), back_inserter(filteredProducts), expensive_filter);
        break;
    }
    case 2: {
        auto electronics_filter = [](const Product& p) { return p.category == "Электроника"; };
        copy_if(products.begin(), products.end(), back_inserter(filteredProducts), electronics_filter);
        break;
    }
    case 3: {
        auto quantity_filter = [](const Product& p) { return p.quantity > 10; };
        copy_if(products.begin(), products.end(), back_inserter(filteredProducts), quantity_filter);
        break;
    }
    case 4: {
        auto cheap_filter = [](const Product& p) { return p.price < 1000; };
        copy_if(products.begin(), products.end(), back_inserter(filteredProducts), cheap_filter);
        break;
    }
    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    ofstream filteredFile("filtered_products.csv");

    if (!filteredFile.is_open()) {
        cout << "Ошибка: не удалось создать файл filtered_products.csv" << endl;
        return 1;
    }

    filteredFile << "id,name,category,price,quantity" << endl;

    for (const auto& p : filteredProducts) {
        filteredFile << p.id << "," << p.name << "," << p.category << ","
            << fixed << setprecision(2) << p.price << "," << p.quantity << endl;
    }

    filteredFile.close();

    cout << endl << "Результаты фильтрации:" << endl;
    cout << "Найдено товаров: " << filteredProducts.size() << endl;
    cout << "Отфильтрованные данные сохранены в filtered_products.csv" << endl;

    return 0;
}