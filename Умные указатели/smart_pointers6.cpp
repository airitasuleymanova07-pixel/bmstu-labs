#include <iostream>
#include <memory>
#include <locale>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    // Создание shared_ptr
    auto ptr1 = make_shared<int>(100);
    cout << "use_count после создания: " << ptr1.use_count() << endl;

    // Создание копий
    auto ptr2 = ptr1;
    auto ptr3 = ptr1;
    cout << "use_count после копирования: " << ptr1.use_count() << endl;

    // Уничтожение одной копии
    ptr2.reset();
    cout << "use_count после reset(): " << ptr1.use_count() << endl;

    return 0;
}