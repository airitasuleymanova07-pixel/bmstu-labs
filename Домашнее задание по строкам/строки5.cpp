#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char str[MAX_SIZE];

    cout << "введите строку: ";
    cin.getline(str, MAX_SIZE);

    int vowels = 0;
    int consonants = 0;

    const char vowel_letters[] = "AEIOUY";

    for (int i = 0; str[i] != '\0'; i++) {
        char current_char = toupper(str[i]);

        if (isalpha(current_char)) {
            bool is_vowel = false;

            for (int j = 0; vowel_letters[j] != '\0'; j++) {
                if (current_char == vowel_letters[j]) {
                    is_vowel = true;
                    break;
                }
            }

            if (is_vowel) {
                vowels++;
            }
            else {
                consonants++;
            }
        }
    }

    cout << "гласных: " << vowels << endl;
    cout << "согласных: " << consonants << endl;

    return 0;
}