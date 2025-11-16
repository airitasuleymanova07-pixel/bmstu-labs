#include <iostream>
#include <memory>
#include <locale>
#include <iomanip>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int n = 3, m = 4;
    auto table = make_unique<int[]>(n * m);

    // Заполнение таблицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            table[i * m + j] = i * j;
        }
    }

    // Вывод таблицы
    cout << "Таблица " << n << "x" << m << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << setw(3) << table[i * m + j] << " ";
        }
        cout << endl;
    }

    return 0;
}