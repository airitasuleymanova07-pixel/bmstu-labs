#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int** transpose(int** matrix, int n, int m) {
    // Создаем новую матрицу с размерами m x n
    int** result = (int**)malloc(m * sizeof(int*));

    for (int i = 0; i < m; i++) {
        result[i] = (int*)malloc(n * sizeof(int));
    }

    // Транспонирование
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void freeMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

int main() {
    int n = 3, m = 4;

    // Создание исходной матрицы
    int** matrix = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        matrix[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            matrix[i][j] = i * m + j + 1;
        }
    }
    setlocale(LC_ALL, "rus");
    printf("Исходная матрица %dx%d:\n", n, m);
    printMatrix(matrix, n, m);

    // Транспонирование
    int** transposed = transpose(matrix, n, m);

    printf("\nТранспонированная матрица %dx%d:\n", m, n);
    printMatrix(transposed, m, n);

    // Освобождение памяти
    freeMatrix(matrix, n);
    freeMatrix(transposed, m);

    return 0;
}