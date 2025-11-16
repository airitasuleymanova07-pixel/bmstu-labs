#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

void sortWords(char** words, int count) {
    // Пузырьковая сортировка указателей на строки
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(words[j], words[j + 1]) > 0) {
                // Меняем указатели местами
                char* temp = words[j];
                words[j] = words[j + 1];
                words[j + 1] = temp;
            }
        }
    }
}

void printWords(char** words, int count) {
    for (int i = 0; i < count; i++) {
        printf("%d: %s\n", i, words[i]);
    }
}

int main() {
    // Массив строк
    char* words[] = {
        "banana", "apple", "grape", "orange",
        "cherry", "pear", "kiwi"
    };
    int count = 7;

    // Создаем копию указателей для сортировки
    char** wordPtrs = (char**)malloc(count * sizeof(char*));
    for (int i = 0; i < count; i++) {
        wordPtrs[i] = words[i];
    }
    setlocale(LC_ALL, "rus");
    printf("Исходный массив слов:\n");
    printWords(wordPtrs, count);

    // Сортировка
    sortWords(wordPtrs, count);

    printf("\nПосле сортировки:\n");
    printWords(wordPtrs, count);

    free(wordPtrs);
    return 0;
}