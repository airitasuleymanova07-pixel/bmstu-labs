#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int n = 10;
    vector <int> A(n);
    setlocale(LC_ALL, "rus");
    cout << "Введите 10 чисел:" << endl;


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

    if (min == 4 && max == 9) {
        cout << "Среднее арифметическое:" << (A[max] + A[min]) / 2 << endl;
    }
    else {
        cout << "Среднее арифметичсекое не считаем" << endl;
    }
    return 0;
}