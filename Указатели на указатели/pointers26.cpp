#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int sumElements(int** arr, int n, int m) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Используем только арифметику указателей
            sum += *(*(arr + i) + j);
        }
    }

    return sum;
}

int main() {
    int n = 3, m = 5;
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
    printf("Массив %dx%d:\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%3d ", arr[i][j]);
        }
        printf("\n");
    }

    // Вычисление суммы через указатели
    int total = sumElements(arr, n, m);
    printf("\nСумма всех элементов: %d\n", total);

    // Проверка обычным способом
    int check_sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            check_sum += arr[i][j];
        }
    }
    printf("Проверка: %d\n", check_sum);

    // Освобождение памяти
    for (int i = 0; i < n; i++) {
        free(arr[i]);
    }
    free(arr);

    return 0;
}