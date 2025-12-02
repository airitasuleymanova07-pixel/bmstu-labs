#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    ofstream outputFile("output.txt");

    if (!outputFile.is_open()) {
        cout << "Ошибка: не удалось создать файл output.txt" << endl;
        return 1;
    }

    string line;

    cout << "Введите строки (пустая строка завершает ввод):" << endl;

    while (true) {
        getline(cin, line);

        if (line.empty()) {
            break;
        }

        outputFile << line << endl;
    }

    outputFile.close();

    cout << "Данные записаны в файл output.txt." << endl;

    return 0;
}