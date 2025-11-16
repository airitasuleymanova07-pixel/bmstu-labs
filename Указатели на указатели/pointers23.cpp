#include <stdio.h>
#include <iostream>
#include <stdlib.h>

void free2D(int** arr, int n) {
    for (int i = 0; i < n; i++) {
        free(arr[i]); // Освобождаем каждую строку
    }
    free(arr); // Освобождаем массив указателей
}

int main() {
    int n = 3, m = 4;
    setlocale(LC_ALL, "rus");
    // Создание массива
    int** arr = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc(m * sizeof(int));
        for (int j = 0; j < m; j++) {
            arr[i][j] = i * m + j + 1;
        }
    }

    // Вывод массива
    printf("Массив перед освобождением:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }

    // Освобождение памяти
    free2D(arr, n);

    printf("Память успешно освобождена!\n");

    return 0;
}