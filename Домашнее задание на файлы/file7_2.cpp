#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
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
        cout << "Сначала создайте файл с помощью программы из Задачи 6" << endl;
        return 1;
    }

    vector<Product> products;
    string line;
    getline(csvFile, line);

    cout << "Список товаров:" << endl;
    cout << "=================================================================" << endl;
    cout << left << setw(5) << "ID" << setw(25) << "Название"
        << setw(15) << "Категория" << setw(10) << "Цена" << setw(10) << "Кол-во" << endl;
    cout << "=================================================================" << endl;

    int lineNumber = 0;
    double totalValue = 0;
    int totalQuantity = 0;
    Product mostExpensive;
    Product cheapest;
    bool first = true;

    while (getline(csvFile, line)) {
        lineNumber++;
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

            cout << left << setw(5) << p.id << setw(25) << p.name.substr(0, 24)
                << setw(15) << p.category.substr(0, 14)
                << setw(10) << fixed << setprecision(2) << p.price
                << setw(10) << p.quantity << endl;

            totalValue += p.price * p.quantity;
            totalQuantity += p.quantity;

            if (first) {
                mostExpensive = p;
                cheapest = p;
                first = false;
            }
            else {
                if (p.price > mostExpensive.price) {
                    mostExpensive = p;
                }
                if (p.price < cheapest.price) {
                    cheapest = p;
                }
            }
        }
    }

    csvFile.close();

    cout << "=================================================================" << endl << endl;

    cout << "Статистика:" << endl;
    cout << "===========" << endl;
    cout << "Общее количество товаров: " << products.size() << endl;
    cout << "Общее количество на складе: " << totalQuantity << " шт." << endl;
    cout << "Общая стоимость всех товаров: " << fixed << setprecision(2) << totalValue << " руб." << endl;
    cout << "Самый дорогой товар: " << mostExpensive.name << " (" << mostExpensive.price << " руб.)" << endl;
    cout << "Самый дешевый товар: " << cheapest.name << " (" << cheapest.price << " руб.)" << endl;

    return 0;
}