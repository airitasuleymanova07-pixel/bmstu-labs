#include <iostream>
#include <cstring>
#include <clocale>

using namespace std;

const char* findSubstring(const char* text, const char* word) {
    if (text == nullptr || word == nullptr) {
        return nullptr;
    }

    if (*word == '\0') {
        return text;
    }

    while (*text != '\0') {
        const char* text_ptr = text;  
        const char* word_ptr = word;  

        while (*text_ptr != '\0' && *word_ptr != '\0' && *text_ptr == *word_ptr) {
            text_ptr++;
            word_ptr++;
        }

        if (*word_ptr == '\0') {
            return text;  
        }

        text++;
    }

    return nullptr;  
}

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 100;
    char text[MAX_SIZE];
    char word[MAX_SIZE];

    cout << "Введите текст: ";
    cin.getline(text, MAX_SIZE);

    cout << "Введите подстроку для поиска: ";
    cin.getline(word, MAX_SIZE);

    const char* result = findSubstring(text, word);

    if (result != nullptr) {
        cout << "Подстрока найдена на позиции: " << (result - text) << endl;
        cout << "Найденный фрагмент: " << result << endl;
    }
    else {
        cout << "Подстрока не найдена!" << endl;
    }

    return 0;
}