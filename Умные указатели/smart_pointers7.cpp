#include <iostream>
#include <memory>
#include <locale>
#include <cstring>
using namespace std;

bool isVowel(char c) {
    c = tolower(c);
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
        c == 'а' || c == 'е' || c == 'и' || c == 'о' || c == 'у';
}

int main() {
    setlocale(LC_ALL, "rus");

    const char* text = "Hello World Programming";
    int length = strlen(text);

    auto strPtr = make_unique<char[]>(length + 1);
    strcpy(strPtr.get(), text);

    // Подсчет гласных и согласных
    int vowels = 0, consonants = 0;
    for (int i = 0; i < length; i++) {
        if (isalpha(strPtr[i])) {
            if (isVowel(strPtr[i])) vowels++;
            else consonants++;
        }
    }

    cout << "Гласные: " << vowels << ", Согласные: " << consonants << endl;

    // Создание массива только с гласными
    auto vowelsPtr = make_unique<char[]>(vowels + 1);
    int index = 0;
    for (int i = 0; i < length; i++) {
        if (isVowel(strPtr[i])) {
            vowelsPtr[index++] = strPtr[i];
        }
    }
    vowelsPtr[vowels] = '\0';

    cout << "Гласные буквы: " << vowelsPtr.get() << endl;

    return 0;
}