#include <iostream>
#include <memory>
#include <vector>
#include <locale>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int n, m;
    cout << "Введите размеры матрицы N и M: ";
    cin >> n >> m;

    // Создание матрицы
    auto matrix = make_unique<double[]>(n * m);

    // Заполнение матрицы
    cout << "Введите элементы матрицы:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i * m + j];
        }
    }

    // Лямбда для суммирования столбцов
    auto sumColumns = [&matrix, n, m]() -> vector<double> {
        vector<double> sums(m, 0);
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                sums[j] += matrix[i * m + j];
            }
        }
        return sums;
        };

    // Лямбда для поиска максимального индекса
    auto maxIndex = [](const vector<double>& sums) -> int {
        return distance(sums.begin(), max_element(sums.begin(), sums.end()));
        };

    // Вычисления
    auto columnSums = sumColumns();
    int maxColIndex = maxIndex(columnSums);

    // Вывод результатов
    cout << "Суммы столбцов: [";
    for (size_t i = 0; i < columnSums.size(); i++) {
        cout << columnSums[i];
        if (i < columnSums.size() - 1) cout << ", ";
    }
    cout << "]" << endl;

    cout << "Столбец с максимальной суммой: " << maxColIndex + 1
        << " (" << columnSums[maxColIndex] << ")" << endl;

    return 0;
}