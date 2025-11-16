#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Функция для вычисления суммы строки
int rowSum(int* row, int m) {
    int sum = 0;
    for (int j = 0; j < m; j++) {
        sum += row[j];
    }
    return sum;
}

// Функция для сортировки строк по сумме элементов
void sortRowsBySum(int** arr, int n, int m) {
    // Пузырьковая сортировка указателей на строки
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (rowSum(arr[j], m) > rowSum(arr[j + 1], m)) {
                // Меняем указатели местами
                int* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void printMatrixWithSums(int** arr, int n, int m) {
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < m; j++) {
            printf("%3d ", arr[i][j]);
            sum += arr[i][j];
        }
        printf("| Сумма: %d\n", sum);
    }
}

int main() {
    int n = 4, m = 3;
    setlocale(LC_ALL, "rus");

    // Создание и заполнение массива
    int** arr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            arr[i][j] = rand() % 10; // числа от 0 до 9
        }
    }

    printf("Исходный массив:\n");
    printMatrixWithSums(arr, n, m);

    // Сортировка
    sortRowsBySum(arr, n, m);

    printf("\nПосле сортировки по сумме:\n");
    printMatrixWithSums(arr, n, m);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}