#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main() {
    int n, m;
    setlocale(LC_ALL, "rus");
    printf("Введите n и m: ");
    scanf_s("%d %d", &n, &m);

    // Выделение памяти для массива указателей
    int** arr = (int**)malloc(n * sizeof(int*));

    // Выделение памяти для каждой строки
    for (int i = 0; i < n; i++) {
        arr[i] = (int*)malloc(m * sizeof(int));
    }

    // Заполнение массива случайными числами
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            arr[i][j] = rand() % 100;
        }
    }

    // Вывод массива
    printf("Массив %dx%d:\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}