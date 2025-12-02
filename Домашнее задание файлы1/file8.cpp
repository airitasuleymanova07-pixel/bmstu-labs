#include <iostream>
#include <fstream>
#include <string>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    ifstream file1("file1.txt");
    ifstream file2("file2.txt");

    if (!file1.is_open()) {
        cout << "Ошибка: не удалось открыть файл file1.txt" << endl;
        return 1;
    }

    if (!file2.is_open()) {
        cout << "Ошибка: не удалось открыть файл file2.txt" << endl;
        file1.close();
        return 1;
    }

    string line1, line2;
    bool identical = true;
    int lineNum = 1;

    while (getline(file1, line1) && getline(file2, line2)) {
        if (line1 != line2) {
            identical = false;
            cout << "Файлы различаются на строке " << lineNum << endl;
            break;
        }
        lineNum++;
    }

    if (identical) {
        if (file1.eof() && file2.eof()) {
            cout << "Файлы идентичны." << endl;
        }
        else {
            cout << "Файлы различаются (разная длина)." << endl;
        }
    }

    file1.close();
    file2.close();

    return 0;
}