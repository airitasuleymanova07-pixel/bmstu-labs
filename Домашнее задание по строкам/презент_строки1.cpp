#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char text[MAX_SIZE];

    cout << "введите строку: ";
    cin.getline(text, MAX_SIZE);

    int len = strlen(text);
    int max_length = 0;      // длина самого длинного слова
    int max_start = 0;       // начало самого длинного слова
    int max_end = 0;         // конец самого длинного слова

    int current_start = 0;   // начало текущего слова
    int current_length = 0;  // длина текущего слова

    for (int i = 0; i <= len; i++) {
        // если текущий символ - буква, увеличиваем длину текущего слова
        if (i < len && isalpha(text[i])) {
            if (current_length == 0) {
                current_start = i; // начало нового слова
            }
            current_length++;
        }
        else {
            // конец слова, проверяем, не самое ли оно длинное
            if (current_length > max_length) {
                max_length = current_length;
                max_start = current_start;
                max_end = i - 1;
            }
            current_length = 0; // сбрасываем для следующего слова
        }
    }

    if (max_length > 0) {
        cout << "самое длинное слово: \"";
        for (int i = max_start; i <= max_end; i++) {
            cout << text[i];
        }
        cout << "\" (длина: " << max_length << " символов)" << endl;
    }
    else {
        cout << "в строке нет слов" << endl;
    }

    return 0;
}