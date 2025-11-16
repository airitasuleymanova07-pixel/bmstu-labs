#include <iostream>
#include <memory>
#include <locale>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    // Создание умного указателя
    unique_ptr<int> ptr = make_unique<int>(10);

    cout << "Значение: " << *ptr << endl;

    // Изменение значения
    *ptr = 25;
    cout << "Новое значение: " << *ptr << endl;

    return 0;
}