#include <iostream>
#include <memory>
#include <vector>
#include <locale>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    // Создание частей отчета
    auto part1 = make_unique<string>("Sensor data:");
    auto part2 = make_unique<string>("Voltage stable.");
    auto part3 = make_unique<string>("System nominal.");

    vector<unique_ptr<string>> reportParts;
    reportParts.push_back(move(part1));
    reportParts.push_back(move(part2));
    reportParts.push_back(move(part3));

    // Лямбда для объединения
    auto concatParts = [](const vector<unique_ptr<string>>& parts) -> string {
        string result;
        for (const auto& part : parts) {
            result += *part + "\n";
        }
        return result;
        };

    // Лямбда для подсчета слов
    auto countWord = [](const string& text, const string& word) -> int {
        int count = 0;
        size_t pos = 0;
        while ((pos = text.find(word, pos)) != string::npos) {
            count++;
            pos += word.length();
        }
        return count;
        };

    // Выполнение операций
    string report = concatParts(reportParts);
    int dataCount = countWord(report, "data");

    cout << "Отчёт:\n" << report << endl;
    cout << "Слово \"data\" встречается " << dataCount << " раз" << endl;

    return 0;
}