#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

// функция для получения отсортированной строки только из букв
void getSortedLetters(const char* input, char* output) {
    int index = 0;

    // извлекаем только буквы и приводим к нижнему регистру
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[index++] = tolower(input[i]);
        }
    }
    output[index] = '\0';

    //сортируем буквы
    sort(output, output + index);
}

int main() {
    setlocale(LC_ALL, "rus");

    char str1[256], str2[256];
    char sorted1[256], sorted2[256];

    cout << "введите первую строку: ";
    cin.getline(str1, 256);

    cout << "введите вторую строку: ";
    cin.getline(str2, 256);

    // получаем отсортированные буквенные последовательности
    getSortedLetters(str1, sorted1);
    getSortedLetters(str2, sorted2);

    cout << "отсортированные буквы строки 1: " << sorted1 << endl;
    cout << "отсортированные буквы строки 2: " << sorted2 << endl;

    // сравниваем отсортированные последовательности
    if (strcmp(sorted1, sorted2) == 0) {
        cout << "да" << endl;
    }
    else {
        cout << "нет" << endl;
    }

    return 0;
}