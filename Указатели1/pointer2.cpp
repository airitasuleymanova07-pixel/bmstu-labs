#include <iostream>
#include <locale>

using namespace std;

void myStrCopy(char* dest, const char* src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_LENGTH = 100;
    char source[MAX_LENGTH];
    char destination[MAX_LENGTH];

    cout << "Введите строку: ";
    cin.getline(source, MAX_LENGTH);

    myStrCopy(destination, source);

    cout << "Исходная: \"" << source << "\"" << endl;
    cout << "Копия: \"" << destination << "\"" << endl;

    return 0;
}