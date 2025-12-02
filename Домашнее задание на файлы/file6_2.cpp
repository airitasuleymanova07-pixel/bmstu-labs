#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale.h>
#include <iomanip>
#include <ctime>
#include <cstdlib>

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
    srand(time(0));

    vector<string> categories = { "Электроника", "Одежда", "Книги", "Продукты", "Спорт" };
    vector<string> electronics = { "Ноутбук", "Смартфон", "Наушники", "Планшет", "Монитор" };
    vector<string> clothes = { "Футболка", "Джинсы", "Куртка", "Рубашка", "Платье" };
    vector<string> books = { "Роман", "Учебник", "Детектив", "Фантастика", "Бизнес" };
    vector<string> foods = { "Хлеб", "Молоко", "Сыр", "Мясо", "Овощи" };
    vector<string> sports = { "Мяч", "Гантели", "Скакалка", "Коврик", "Ракетка" };

    ofstream csvFile("products.csv");

    if (!csvFile.is_open()) {
        cout << "Ошибка: не удалось создать файл products.csv" << endl;
        return 1;
    }

    csvFile << "id,name,category,price,quantity" << endl;

    for (int i = 1; i <= 20; i++) {
        int categoryIndex = rand() % categories.size();
        string category = categories[categoryIndex];
        string name;

        if (category == "Электроника") {
            name = electronics[rand() % electronics.size()] + " " + to_string(rand() % 1000);
        }
        else if (category == "Одежда") {
            name = clothes[rand() % clothes.size()] + " " + to_string(rand() % 1000);
        }
        else if (category == "Книги") {
            name = books[rand() % books.size()] + " " + to_string(rand() % 1000);
        }
        else if (category == "Продукты") {
            name = foods[rand() % foods.size()] + " " + to_string(rand() % 1000);
        }
        else {
            name = sports[rand() % sports.size()] + " " + to_string(rand() % 1000);
        }

        double price = 100 + rand() % 9900 + (rand() % 100) / 100.0;
        int quantity = 1 + rand() % 100;

        csvFile << i << "," << name << "," << category << ","
            << fixed << setprecision(2) << price << "," << quantity << endl;
    }

    csvFile.close();

    cout << "Файл products.csv успешно создан" << endl;
    cout << "Создано 20 товаров со случайными данными" << endl;

    return 0;
}