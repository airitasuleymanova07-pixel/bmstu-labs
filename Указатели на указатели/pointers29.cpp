#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

double** allocateWeights(int n, int m) {
    double** weights = (double**)malloc(n * sizeof(double*));
    for (int i = 0; i < n; i++) {
        weights[i] = (double*)malloc(m * sizeof(double));
    }
    return weights;
}

void freeWeights(double** weights, int n) {
    for (int i = 0; i < n; i++) {
        free(weights[i]);
    }
    free(weights);
}

void initializeWeights(double** weights, int n, int m) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Случайные веса от -1.0 до 1.0
            weights[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0;
        }
    }
}

void normalizeWeights(double** weights, int n, int m) {
    for (int i = 0; i < n; i++) {
        double sum = 0.0;
        // Сумма абсолютных значений весов в строке
        for (int j = 0; j < m; j++) {
            sum += abs(weights[i][j]);
        }

        // Нормализация, если сумма > 1
        if (sum > 1.0) {
            for (int j = 0; j < m; j++) {
                weights[i][j] /= sum;
            }
        }
    }
}

double* forward(double** weights, double* inputs, int n, int m) {
    double* outputs = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        outputs[i] = 0.0;
        for (int j = 0; j < m; j++) {
            outputs[i] += weights[i][j] * inputs[j];
        }
    }

    return outputs;
}

void printMatrixDouble(double** matrix, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%8.3f ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printArrayDouble(double* array, int n) {
    for (int i = 0; i < n; i++) {
        printf("%8.3f ", array[i]);
    }
    printf("\n");
}

int main() {
    int n = 3; // Количество нейронов
    int m = 4; // Количество входов

    // Создание и инициализация весов
    double** weights = allocateWeights(n, m);
    initializeWeights(weights, n, m);
    setlocale(LC_ALL, "rus");
    printf("Исходные веса:\n");
    printMatrixDouble(weights, n, m);

    // Нормализация весов
    normalizeWeights(weights, n, m);
    printf("\nПосле нормализации:\n");
    printMatrixDouble(weights, n, m);

    // Создание входного вектора
    double* inputs = (double*)malloc(m * sizeof(double));
    for (int j = 0; j < m; j++) {
        inputs[j] = (double)(j + 1) * 0.5; // 0.5, 1.0, 1.5, 2.0
    }

    printf("\nВходные сигналы:\n");
    printArrayDouble(inputs, m);

    // Прямое распространение
    double* outputs = forward(weights, inputs, n, m);

    printf("\nВыходы нейронов:\n");
    printArrayDouble(outputs, n);

    // Освобождение памяти
    freeWeights(weights, n);
    free(inputs);
    free(outputs);

    return 0;
}