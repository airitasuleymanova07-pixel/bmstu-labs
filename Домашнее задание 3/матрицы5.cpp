#include <iostream>
using namespace std;

int main() {
    int n, m;
    setlocale(LC_ALL, "rus");
    cout << "¬ведите размер массива:";
    cin >> n >> m;

    int matrix[100][100];

    cout << "¬ведите элементы массива:";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    // границы 
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top <= bottom && left <= right) {
        // вправо по верхней строке
        for (int j = left; j <= right; j++) {
            cout << matrix[top][j] << " ";
        }
        top++;

        // вниз по правому столбцу
        for (int i = top; i <= bottom; i++) {
            cout << matrix[i][right] << " ";
        }
        right--;

        // проверка, есть ли еще строки дл€ обхода слева направо
        if (top <= bottom) {
            // влево по нижней строке
            for (int j = right; j >= left; j--) {
                cout << matrix[bottom][j] << " ";
            }
            bottom--;
        }

        // проверка, есть ли еще столбцы дл€ обхода снизу вверх
        if (left <= right) {
            // вверх по левому столбцу
            for (int i = bottom; i >= top; i--) {
                cout << matrix[i][left] << " ";
            }
            left++;
        }
    }

    return 0;
}