#include <iostream>
using namespace std;

int main() {
    int n;
    setlocale(LC_ALL, "rus");
    cout << "¬ведите размер матрицы:";
    cin >> n;

    int matrix[100][100] = { 0 };

    int num = 1;
    int top = 0, bottom = n - 1, left = 0, right = n - 1;

    while (num <= n * n) {
        // вправо по верхней строке
        for (int j = left; j <= right; j++) {
            matrix[top][j] = num++;
        }
        top++;

        // вниз по правому столбцу
        for (int i = top; i <= bottom; i++) {
            matrix[i][right] = num++;
        }
        right--;

        // влево по нижней строке
        for (int j = right; j >= left; j--) {
            matrix[bottom][j] = num++;
        }
        bottom--;

        // вверх по левому столбцу
        for (int i = bottom; i >= top; i--) {
            matrix[i][left] = num++;
        }
        left++;
    }

    // вывод матрицы
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j];
            if (j < n - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}