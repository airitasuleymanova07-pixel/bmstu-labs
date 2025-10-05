#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int n = 10;
    vector<int> A(n);

    setlocale(LC_ALL, "rus");
    cout << "Введите 10 целых чисел:" << endl;
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

    if (max == 1 && min == 4) {
        cout << "Устанавливаем элементы с " << min + 1 << "-й по " << n << "-ю позицию равными " << A[max] << endl;
        for (int i = min; i < n; i++) {
            A[i] = A[max];
        }
        cout << "Новый массив:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "A[" << i + 1 << "] = " << A[i] << endl;
        }
    }
    else {
        if (max != 1) {
            cout << "Максимальный элемент не на 2-й позиции" << endl;
        }
        if (min != 4) {
            cout << "Минимальный элемент не на 5-й позиции" << endl;
        }
    }

    return 0;
}
