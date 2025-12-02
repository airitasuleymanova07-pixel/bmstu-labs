#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    ifstream logFile("application.log");

    if (!logFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл application.log" << endl;
        return 1;
    }

    const int LINES_PER_PART = 100;
    int partNumber = 1;
    int lineCount = 0;
    vector<string> partFiles;
    ofstream currentPart;
    ofstream indexFile("log_index.txt");

    string line;
    while (getline(logFile, line)) {
        if (lineCount % LINES_PER_PART == 0) {
            if (currentPart.is_open()) {
                currentPart.close();
            }

            string partName = "log_part" + to_string(partNumber) + ".txt";
            partFiles.push_back(partName);
            currentPart.open(partName);

            if (!currentPart.is_open()) {
                cout << "Ошибка: не удалось создать файл " << partName << endl;
                return 1;
            }

            partNumber++;
        }

        currentPart << line << endl;
        lineCount++;
    }

    logFile.close();
    if (currentPart.is_open()) {
        currentPart.close();
    }

    indexFile << "Индекс файлов логов:" << endl;
    indexFile << "=====================" << endl;
    indexFile << "Исходный файл: application.log" << endl;
    indexFile << "Всего строк: " << lineCount << endl;
    indexFile << "Частей создано: " << partFiles.size() << endl << endl;

    for (size_t i = 0; i < partFiles.size(); i++) {
        indexFile << "Часть " << i + 1 << ": " << partFiles[i] << endl;
    }

    indexFile.close();

    cout << "Лог-файл разделен на " << partFiles.size() << " частей" << endl;
    cout << "Создан файл индекса: log_index.txt" << endl;

    return 0;
}