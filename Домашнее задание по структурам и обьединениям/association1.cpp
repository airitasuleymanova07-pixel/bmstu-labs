#include <iostream>
#include <locale.h>

using namespace std;

union Variant {
    int intValue;
    double doubleValue;
    char charValue;
};

int main() {
    setlocale(LC_ALL, "rus");

    Variant data;
    char choice;

    cout << "Выберите тип данных (i - целое число, d - число с плавающей запятой, c - символ): ";
    cin >> choice;

    switch (choice) {
    case 'i':
    case 'I':
        cout << "Введите целое число: ";
        cin >> data.intValue;
        cout << "Вы ввели: " << data.intValue << endl;
        break;

    case 'd':
    case 'D':
        cout << "Введите число с плавающей запятой: ";
        cin >> data.doubleValue;
        cout << "Вы ввели: " << data.doubleValue << endl;
        break;

    case 'c':
    case 'C':
        cout << "Введите символ: ";
        cin >> data.charValue;
        cout << "Вы ввели: " << data.charValue << endl;
        break;

    default:
        cout << "Неверный выбор!" << endl;
    }

    return 0;
}