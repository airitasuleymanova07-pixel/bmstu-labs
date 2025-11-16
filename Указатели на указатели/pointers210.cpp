#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Функция для создания матрицы нагрузок
int** createLoadMatrix(int n, int t) {
    int** load = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        load[i] = (int*)malloc(t * sizeof(int));
    }
    return load;
}

// Функция для освобождения матрицы
void freeLoadMatrix(int** load, int n) {
    for (int i = 0; i < n; i++) {
        free(load[i]);
    }
    free(load);
}

// Функция для ввода данных
void inputLoadData(int** load, int n, int t) {
    printf("Введите нагрузку для каждого узла по интервалам:\n");
    for (int i = 0; i < n; i++) {
        printf("Узел %d: ", i);
        for (int j = 0; j < t; j++) {
            scanf_s("%d", &load[i][j]);
            // Проверка корректности ввода
            if (load[i][j] < 0 || load[i][j] > 100) {
                printf("Ошибка: нагрузка должна быть в диапазоне 0-100%%\n");
                j--; // Повторяем ввод для этого элемента
            }
        }
    }
}

// Функция для красивого вывода матрицы
void printMatrix(int** load, int n, int t) {
    printf("\nМатрица нагрузок:\n");
    printf("Узел\\Время");
    for (int j = 0; j < t; j++) {
        printf("%6d", j);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        printf("Узел %d:  ", i);
        for (int j = 0; j < t; j++) {
            printf("%6d%%", load[i][j]);
        }
        printf("\n");
    }
}

// Этап 1: Средняя нагрузка по узлам
double* averageLoadPerNode(int** load, int n, int t) {
    double* averages = (double*)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < t; j++) {
            // Используем арифметику указателей
            sum += *(*(load + i) + j);
        }
        averages[i] = (double)sum / t;
    }

    return averages;
}

// Этап 2: Нормализация нагрузки
void normalizeLoad(int** load, int n, int t) {
    for (int j = 0; j < t; j++) {
        for (int i = 0; i < n; i++) {
            if (load[i][j] > 80) {
                // Находим перегруженный узел
                int overload = load[i][j];
                int reduction = overload * 0.1; // 10% от нагрузки

                // Распределяем между остальными узлами
                int nodes_to_distribute = n - 1;
                if (nodes_to_distribute > 0) {
                    int per_node = reduction / nodes_to_distribute;

                    // Уменьшаем нагрузку перегруженного узла
                    load[i][j] -= reduction;

                    // Увеличиваем нагрузку остальных узлов
                    for (int k = 0; k < n; k++) {
                        if (k != i && load[k][j] + per_node <= 100) {
                            load[k][j] += per_node;
                        }
                    }
                }
            }
        }
    }
}

// Этап 3: Поиск критического интервала
int findCriticalInterval(int** load, int n, int t) {
    int max_sum = 0;
    int critical_interval = 0;

    for (int j = 0; j < t; j++) {
        int interval_sum = 0;
        for (int i = 0; i < n; i++) {
            // Используем арифметику указателей
            interval_sum += *(*(load + i) + j);
        }

        if (interval_sum > max_sum) {
            max_sum = interval_sum;
            critical_interval = j;
        }
    }

    return critical_interval;
}

// Функция для вывода средних нагрузок
void printAverages(double* averages, int n) {
    printf("\nСредняя нагрузка по узлам:\n");
    for (int i = 0; i < n; i++) {
        printf("Узел %d: %.1f%%\n", i, averages[i]);
    }
}

int main() {
    int N, T;
    setlocale(LC_ALL, "rus");
    printf("Введите количество узлов и интервалов: ");
    scanf_s("%d %d", &N, &T);

    // Создание матрицы нагрузок
    int** load = createLoadMatrix(N, T);

    // Ввод данных
    inputLoadData(load, N, T);

    // Вывод исходной матрицы
    printf("\n=== ИСХОДНЫЕ ДАННЫЕ ===");
    printMatrix(load, N, T);

    // Этап 1: Расчет средней нагрузки
    double* averages = averageLoadPerNode(load, N, T);
    printAverages(averages, N);

    // Этап 2: Нормализация нагрузки
    normalizeLoad(load, N, T);
    printf("\n=== ПОСЛЕ НОРМАЛИЗАЦИИ ===");
    printMatrix(load, N, T);

    // Вывод новых средних значений
    double* new_averages = averageLoadPerNode(load, N, T);
    printAverages(new_averages, N);

    // Этап 3: Поиск критического интервала
    int critical = findCriticalInterval(load, N, T);

    // Расчет суммарной нагрузки в критическом интервале
    int total_critical_load = 0;
    for (int i = 0; i < N; i++) {
        total_critical_load += load[i][critical];
    }

    printf("\nКритический интервал: %d (суммарная нагрузка = %d%%)",
        critical, total_critical_load);

    // Освобождение памяти
    freeLoadMatrix(load, N);
    free(averages);
    free(new_averages);

    return 0;
}