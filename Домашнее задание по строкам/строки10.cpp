#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char text[MAX_SIZE];

    cout << "введите строку: ";
    cin.getline(text, MAX_SIZE);

    int len = strlen(text);
    int start = 0; 
    for (int i = 0; i <= len; i++) {
        if (text[i] == ' ' || text[i] == '\0') {
            reverse(text + start, text + i);
            start = i + 1; 
        }
    }

    cout << "результат: " << text << endl;

    return 0;
}