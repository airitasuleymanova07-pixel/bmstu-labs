#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    // 1. Создаем исходный файл source.txt с произвольным текстом
    ofstream createFile("source.txt");

    if (!createFile.is_open()) {
        cout << "Ошибка: не удалось создать файл source.txt" << endl;
        return 1;
    }

    // Записываем произвольный текст в файл
    createFile << "Это первая строка текста." << endl;
    createFile << "Вторая строка содержит числа: 12345" << endl;
    createFile << "Третья строка с разными символами: !@#$%" << endl;
    createFile << "Четвертая строка" << endl;
    createFile << "Пятая строка" << endl;
    createFile << "Шестая строка" << endl;
    createFile << "Седьмая строка" << endl;
    createFile << "Восьмая строка - последняя" << endl;

    createFile.close();
    cout << "Файл source.txt успешно создан." << endl;

    // 2. Теперь копируем содержимое в новый файл
    ifstream sourceFile("source.txt");

    if (!sourceFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл source.txt для чтения" << endl;
        return 1;
    }

    ofstream copyFile("copy.txt");

    if (!copyFile.is_open()) {
        cout << "Ошибка: не удалось создать файл copy.txt" << endl;
        sourceFile.close();
        return 1;
    }

    string line;
    int lineCount = 0;

    // Копируем содержимое построчно
    while (getline(sourceFile, line)) {
        copyFile << line << endl;
        lineCount++;
    }

    // Закрываем файлы
    sourceFile.close();
    copyFile.close();

    // Выводим результат
    cout << "Файл успешно скопирован." << endl;
    cout << "Количество скопированных строк: " << lineCount << endl;

    return 0;
}