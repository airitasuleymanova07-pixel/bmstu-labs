#include <stdio.h>
#include <stdlib.h>
#include <iostream>

double** allocatePlate(int n, int m) {
    double** plate = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        plate[i] = (double*)malloc(m * sizeof(double));
    }
    return plate;
}

void freePlate(double** plate, int n) {
    for (int i = 0; i < n; i++) {
        free(plate[i]);
    }
    free(plate);
}

void initializePlate(double** plate, int n, int m) {
    // Инициализация всей пластины 20.0 градусами
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            plate[i][j] = 20.0;
        }
    }

    // Нагреватель в центре
    int center_i = n / 2;
    int center_j = m / 2;
    plate[center_i][center_j] = 100.0;
}

void updateTemperature(double** plate, int n, int m) {
    // Создаем временный массив для новых температур
    double** newPlate = allocatePlate(n, m);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == n / 2 && j == m / 2) {
                // Нагреватель - фиксированная температура
                newPlate[i][j] = 100.0;
            }
            else {
                // Среднее арифметическое соседей
                double sum = 0.0;
                int count = 0;

                if (i > 0) { sum += plate[i - 1][j]; count++; }
                if (i < n - 1) { sum += plate[i + 1][j]; count++; }
                if (j > 0) { sum += plate[i][j - 1]; count++; }
                if (j < m - 1) { sum += plate[i][j + 1]; count++; }

                newPlate[i][j] = sum / count;
            }
        }
    }

    // Копируем новые значения обратно
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            plate[i][j] = newPlate[i][j];
        }
    }

    freePlate(newPlate, n);
}

void printPlate(double** plate, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%6.1f ", plate[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int n = 5, m = 5; // Размер пластины
    int iterations = 10; // Количество итераций

    double** plate = allocatePlate(n, m);
    initializePlate(plate, n, m);
    setlocale(LC_ALL, "rus");
    printf("Начальное состояние пластины:\n");
    printPlate(plate, n, m);

    for (int iter = 0; iter < iterations; iter++) {
        updateTemperature(plate, n, m);
        printf("\nПосле итерации %d:\n", iter + 1);
        printPlate(plate, n, m);
    }

    freePlate(plate, n);
    return 0;
}