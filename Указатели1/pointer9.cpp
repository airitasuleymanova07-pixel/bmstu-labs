#include <iostream>
#include <cstring>
#include <clocale>

using namespace std;

void removeSpaces(char* str) {
    if (str == nullptr || *str == '\0') {
        return;  
    }

    char* read_ptr = str;   //  для чтения символов (двигается по всей строке)
    char* write_ptr = str;  //  для записи символов (двигается только для не-пробелов)

    while (*read_ptr != '\0') {
        if (*read_ptr != ' ') {
            *write_ptr = *read_ptr;  
            write_ptr++;            
        }
        read_ptr++;
    }

    *write_ptr = '\0';
}

int main() {
    setlocale(LC_ALL, "rus");  
    const int MAX_SIZE = 256;
    char text[MAX_SIZE];

    cout << "Введите строку с пробелами: ";
    cin.getline(text, MAX_SIZE);

    cout << "Исходная строка:" << text << endl;
    cout << "Длина исходной строки: " << strlen(text) << endl;

    removeSpaces(text);

    cout << "Строка без пробелов:" << text << endl;
    cout << "Длина строки без пробелов: " << strlen(text) << endl;

    return 0;
}