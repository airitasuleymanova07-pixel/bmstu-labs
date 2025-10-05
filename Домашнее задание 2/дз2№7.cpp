#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int n = 15;
    vector<int> A(n);
    setlocale(LC_ALL, "rus");
    cout << "Введите 15 целых чисел:" << endl;

    for (int i = 0; i < n; i++) {
        cout << "Элемент " << i + 1 << ": ";
        cin >> A[i];
    }

    int min = 0, max = 0;

    for (int i = 1; i < n; i++) {
        if (A[i] < A[min]) {
            min = i;
        }
        if (A[i] > A[max]) {
            max = i;
        }
    }

    cout << "Минимальный элемент: " << A[min] << " (позиция " << min + 1 << ")" << endl;
    cout << "Максимальный элемент: " << A[max] << " (позиция " << max + 1 << ")" << endl;

    if (A[min] == 0 || A[max] == 0) {
        cout << "Обнуляем элементы, предшествующие минимальному." << endl;

        for (int i = 0; i < min; i++) {
            A[i] = 0;
        }

        cout << "Новый массив:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "A[" << i + 1 << "] = " << A[i] << endl;
        }
    }
    else {
        cout << "Условие НЕ выполняется." << endl;
    }

    return 0;
}