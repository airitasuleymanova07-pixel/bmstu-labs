#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    ifstream bookFile("book.txt");
    ofstream resultFile("search_results.txt");

    if (!bookFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл book.txt" << endl;
        return 1;
    }

    if (!resultFile.is_open()) {
        cout << "Ошибка: не удалось создать файл search_results.txt" << endl;
        bookFile.close();
        return 1;
    }

    string searchWord = "герой";
    string line;
    int lineNumber = 0;
    int totalFound = 0;
    vector<pair<int, int>> positions;

    resultFile << "Результаты поиска слова '" << searchWord << "':" << endl;
    resultFile << "==============================" << endl;

    while (getline(bookFile, line)) {
        lineNumber++;
        size_t pos = 0;

        while ((pos = line.find(searchWord, pos)) != string::npos) {
            positions.push_back(make_pair(lineNumber, pos + 1));
            resultFile << "Строка: " << lineNumber
                << ", Позиция: " << pos + 1
                << ", Контекст: ";

            int start = (pos > 20) ? pos - 20 : 0;
            int length = (line.length() - start > 50) ? 50 : line.length() - start;
            resultFile << line.substr(start, length) << "..." << endl;

            pos += searchWord.length();
            totalFound++;
        }
    }

    resultFile << "==============================" << endl;
    resultFile << "Всего найдено: " << totalFound << " вхождений" << endl;

    bookFile.close();
    resultFile.close();

    cout << "Поиск завершен. Результаты сохранены в search_results.txt" << endl;
    cout << "Найдено " << totalFound << " вхождений слова '" << searchWord << "'" << endl;

    return 0;
}