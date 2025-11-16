#include <iostream>
#include <memory>
#include <locale>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    // Создание умного указателя
    auto ptr1 = make_unique<int>(42);
    cout << "ptr1: " << *ptr1 << endl;

    // Передача владения
    auto ptr2 = move(ptr1);

    // Проверка
    if (ptr1 == nullptr) {
        cout << "ptr1 теперь nullptr" << endl;
    }

    cout << "ptr2: " << *ptr2 << endl;

    return 0;
}