#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    string filename = "config.txt";
    fstream configFile(filename, ios::in | ios::out);
    vector<char> buffer;

    if (!configFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return 1;
    }

    char ch;
    while (configFile.get(ch)) {
        buffer.push_back(ch);
    }

    string fileContent(buffer.begin(), buffer.end());

    string searchParam = "timeout=";
    size_t pos = fileContent.find(searchParam);

    if (pos != string::npos) {
        size_t valueStart = pos + searchParam.length();
        size_t valueEnd = fileContent.find("\n", valueStart);
        if (valueEnd == string::npos) valueEnd = fileContent.length();

        string oldValue = fileContent.substr(valueStart, valueEnd - valueStart);
        cout << "Найден параметр timeout. Текущее значение: " << oldValue << endl;

        string newValue;
        cout << "Введите новое значение для timeout: ";
        cin >> newValue;

        fileContent.replace(valueStart, valueEnd - valueStart, newValue);

        configFile.close();
        configFile.open(filename, ios::out | ios::trunc);
        configFile << fileContent;

        cout << "Значение параметра timeout изменено на: " << newValue << endl;
    }
    else {
        cout << "Параметр timeout не найден в файле" << endl;
    }

    configFile.close();

    return 0;
}