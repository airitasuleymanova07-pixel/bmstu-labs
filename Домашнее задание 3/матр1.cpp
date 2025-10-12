#include <iostream>
using namespace std;
// ƒействи€ с матрицой 
void transpose(int n, int matrix[][100], int result[][100]) { //отражени€ относительно главной диагонали
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[j][i];
        }
    }
}

void antiTranspose(int n, int matrix[][100], int result[][100]) { //отражени€ относительно побочной диагонали
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[n - 1 - j][n - 1 - i];
        }
    }
}

void verticalReflection(int n, int matrix[][100], int result[][100]) { //зеркального отражени€ относительно вертикальной оси
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[i][n - 1 - j];
        }
    }
}

void horizontalReflection(int n, int matrix[][100], int result[][100]) {  //зеркального отражени€ относительно горизонтальной оси
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[n - 1 - i][j];
        }
    }
}

bool areMatricesEqual(int n, int mat1[][100], int mat2[][100]) { // сравнени€ двух матриц
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat1[i][j] != mat2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void printMatrix(int n, int matrix[][100]) { //вывод матриц
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j];
            if (j < n - 1) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    setlocale(LC_ALL, "rus");
    // ввод размера матрицы
    cout << "¬ведите размер матрицы N: ";
    cin >> n;

    // проверка 
    if (n < 1 || n > 100) {
        cout << "ќшибка: размер матрицы должен быть от 1 до 100" << endl;
        return 1;
    }

    // объ€вление, макс размер
    int matrix[100][100];
    int matrix1[100][100], matrix2[100][100], matrix3[100][100], matrix4[100][100];

    // ввод элементов
    cout << "¬ведите элементы матрицы " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "Ёлемент [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }

    transpose(n, matrix, matrix1);
    antiTranspose(n, matrix, matrix2);
    verticalReflection(n, matrix, matrix3);
    horizontalReflection(n, matrix, matrix4);

    cout << "»сходна€ матрица:" << endl;
    printMatrix(n, matrix);

    cout << "ћатрица 1 (отражение относительно главной диагонали):" << endl;
    printMatrix(n, matrix1);

    cout << "ћатрица 2 (отражение относительно побочной диагонали):" << endl;
    printMatrix(n, matrix2);

    cout << "ћатрица 3 (зеркальное отражение относительно вертикальной оси):" << endl;
    printMatrix(n, matrix3);

    cout << "ћатрица 4 (зеркальное отражение относительно горизонтальной оси):" << endl;
    printMatrix(n, matrix4);

    // сравнение 
    int matrices[4][100][100];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrices[0][i][j] = matrix1[i][j];
            matrices[1][i][j] = matrix2[i][j];
            matrices[2][i][j] = matrix3[i][j];
            matrices[3][i][j] = matrix4[i][j];
        }
    }

    // поиск совпадающих пар
    bool foundMatches = false;
    cout << "—овпадающие матрицы:" << endl;

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (areMatricesEqual(n, matrices[i], matrices[j])) {
                cout << "ћатрица " << i + 1 << " и ћатрица " << j + 1 << " совпадают" << endl;
                foundMatches = true;
            }
        }
    }

    if (!foundMatches) {
        cout << "NONE" << endl;
    }

    return 0;
}