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
    cout << "Выберите критерий сортировки:" << endl;
    cout << "1. По цене (от дешевых к дорогим)" << endl;
    cout << "2. По цене (от дорогих к дешевым)" << endl;
    cout << "3. По названию (алфавитный порядок)" << endl;
    cout << "4. По количеству (от большего к меньшему)" << endl;
    cout << "Введите номер: ";
    cin >> choice;

    switch (choice) {
    case 1: {
        auto price_asc = [](const Product& a, const Product& b) { return a.price < b.price; };
        sort(products.begin(), products.end(), price_asc);
        break;
    }
    case 2: {
        auto price_desc = [](const Product& a, const Product& b) { return a.price > b.price; };
        sort(products.begin(), products.end(), price_desc);
        break;
    }
    case 3: {
        auto name_asc = [](const Product& a, const Product& b) { return a.name < b.name; };
        sort(products.begin(), products.end(), name_asc);
        break;
    }
    case 4: {
        auto quantity_desc = [](const Product& a, const Product& b) { return a.quantity > b.quantity; };
        sort(products.begin(), products.end(), quantity_desc);
        break;
    }
    default:
        cout << "Неверный выбор!" << endl;
        return 1;
    }

    ofstream sortedFile("sorted_products.csv");

    if (!sortedFile.is_open()) {
        cout << "Ошибка: не удалось создать файл sorted_products.csv" << endl;
        return 1;
    }

    sortedFile << "id,name,category,price,quantity" << endl;

    for (const auto& p : products) {
        sortedFile << p.id << "," << p.name << "," << p.category << ","
            << fixed << setprecision(2) << p.price << "," << p.quantity << endl;
    }

    sortedFile.close();

    cout << endl << "Товары отсортированы. Результаты сохранены в sorted_products.csv" << endl;

    return 0;
}