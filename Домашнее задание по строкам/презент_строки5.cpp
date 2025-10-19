#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    char text[256];
    char words[100][100]; // массив для хранения слов
    int word_count = 0;
    int char_index = 0;

    cout << "введите строку: ";
    cin.getline(text, 256);

    int len = strlen(text);
    bool in_word = false;

    for (int i = 0; i <= len; i++) {
        if (isalpha(text[i]) && !in_word) {
            // начало нового слова
            in_word = true;
            char_index = 0;
            words[word_count][char_index++] = text[i];
        }
        else if (isalpha(text[i]) && in_word) {
            // продолжение слова
            words[word_count][char_index++] = text[i];
        }
        else if (!isalpha(text[i]) && in_word) {
            // конец слова
            words[word_count][char_index] = '\0';
            word_count++;
            in_word = false;
        }
    }

    cout << "найдено слов: " << word_count << endl;
    cout << "слова:" << endl;

    for (int i = 0; i < word_count; i++) {
        cout << words[i] << endl;
    }

    return 0;
}