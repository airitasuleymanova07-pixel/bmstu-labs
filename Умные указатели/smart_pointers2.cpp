#include <iostream>
#include <memory>
#include <locale>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    // Создание динамического массива
    auto arr = make_unique<int[]>(n);

    // Заполнение массива
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Вывод массива
    cout << "Массив: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}