#include <iostream>
using namespace std;

int main() {
    int n;
    setlocale(LC_ALL, "rus");
    cout << "¬ведите размер матрицы:";
    cin >> n;

    int matrix[50][50];

    cout << "¬ведите элементы матрицы " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Ёлемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }

    // сумма, с которой сравнивают
    int localSum = 0;
    for (int i = 0; i < n; i++) {
        localSum += matrix[i][i];
    }

    // побочна€ диагональ
    int Sum2 = 0;
    for (int i = 0; i < n; i++) {
        Sum2 += matrix[i][n - 1 - i];
    }
    if (Sum2 != localSum) {
        cout << "NO" << endl;
        return 0;
    }

    // строк
    for (int i = 0; i < n; i++) {
        int Sum3 = 0;
        for (int j = 0; j < n; j++) {
            Sum3 += matrix[i][j];
        }
        if (Sum3 != localSum) {
            cout << "NO" << endl;
            return 0;
        }
    }

    // столбцы
    for (int j = 0; j < n; j++) {
        int Sum4 = 0;
        for (int i = 0; i < n; i++) {
            Sum4 += matrix[i][j];
        }
        if (Sum4 != localSum) {
            cout << "NO" << endl;
            return 0;
        }
    }
    // проверка
    cout << "YES" << endl;
    cout << localSum << endl;

    return 0;
}