#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU.UTF-8");

    const int MAX_SIZE = 256;
    char input[MAX_SIZE];

    cout << "введите строку: ";
    cin.getline(input, MAX_SIZE);

    char processed[MAX_SIZE];
    int processed_len = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        if (!isspace(input[i])) {
            processed[processed_len] = tolower(input[i]);
            processed_len++;
        }
    }
    processed[processed_len] = '\0'; 

    bool is_palindrome = true;
    for (int i = 0; i < processed_len / 2; i++) {
        if (processed[i] != processed[processed_len - 1 - i]) {
            is_palindrome = false;
            break;
        }
    }

    if (is_palindrome) {
        cout << "это палиндром" << endl;
    }
    else {
        cout << "это не палиндром" << endl;
    }

    return 0;
}