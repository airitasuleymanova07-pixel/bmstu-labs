#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int n = 15;
    vector<double> A(n);
    setlocale(LC_ALL, "rus");
    cout << "Введите 15 вещественных чисел:" << endl;
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

    if (min == 1 && max == 0) {
        cout << "Условие выполняется. Уменьшаем все элементы в 2 раза." << endl;

        for (int i = 0; i < n; i++) {
            A[i] = A[i] / 2.0;
        }

        cout << "Новый массив:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "A[" << i + 1 << "] = " << A[i] << endl;
        }
    }
    else {
        cout << "Условие НЕ выполняется" << endl;
        cout << "Массив остается без изменений" << endl;
    }

    return 0;
}
