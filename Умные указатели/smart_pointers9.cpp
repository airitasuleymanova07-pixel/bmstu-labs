#include <iostream>
#include <memory>
#include <vector>
#include <locale>
using namespace std;

void processA(shared_ptr<vector<int>> buf) {
    for (auto& num : *buf) {
        num += 1;
    }
}

void processB(shared_ptr<vector<int>> buf) {
    for (auto& num : *buf) {
        num *= 2;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    // Создание общего буфера
    auto buffer = make_shared<vector<int>>();

    // Заполнение числами 1-10
    for (int i = 1; i <= 10; i++) {
        buffer->push_back(i);
    }

    cout << "Исходный буфер: ";
    for (auto num : *buffer) {
        cout << num << " ";
    }
    cout << endl;

    // Обработка
    processA(buffer);
    processB(buffer);

    cout << "После обработки: ";
    for (auto num : *buffer) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}