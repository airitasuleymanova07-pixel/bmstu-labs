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

    if (max < min) {
        double product = A[min] * A[max];
        cout << "Максимальный элемент предшествует минимальному." << endl;
        cout << "Произведение минимального и максимального элементов: "
            << A[min] << " * " << A[max] << " = " << product << endl;
    }
    else {
        cout << "Максимальный элемент НЕ предшествует минимальному." << endl;
        cout << "Произведение не вычисляется." << endl;
    }

    return 0;
}