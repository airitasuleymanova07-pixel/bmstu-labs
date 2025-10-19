#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char text[MAX_SIZE];

    cout << "введите текст: ";
    cin.getline(text, MAX_SIZE);

    int len = strlen(text);
    bool new_sentence = true; 
    for (int i = 0; i < len; i++) {
        if (new_sentence && isalpha(text[i])) {
            text[i] = toupper(text[i]);
            new_sentence = false;
        }
        else if (isalpha(text[i])) {
            text[i] = tolower(text[i]);
        }

        if (text[i] == '.' || text[i] == '!' || text[i] == '?') {
            new_sentence = true;
        }
    }

    cout << "исправленный текст: " << text << endl;

    return 0;
}