#include <iostream>

int myStrLen(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}
using namespace std;
int main() {
    setlocale(LC_ALL, "rus");
    const int MAX_LENGTH = 100;
    char userInput[MAX_LENGTH];  // Буфер для хранения ввода пользователя
    cout << "Введите строку: ";
    cin.getline(userInput, MAX_LENGTH);
    int length = myStrLen(userInput);
    cout << "Вы ввели: \"" << userInput << "\"" << std::endl;
    cout << "Длина строки: " << length << " символов" << std::endl;

    return 0;
}