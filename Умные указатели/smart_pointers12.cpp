#include <iostream>
#include <memory>
#include <vector>
#include <locale>
#include <algorithm>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    vector<string> logs = {
        "INFO: Start",
        "ERROR: Disk failure",
        "WARNING: Low memory",
        "ERROR: Disk failure",
        "INFO: Stop"
    };

    // Обертывание в shared_ptr
    auto logPtr = make_shared<vector<string>>(logs);

    // Фильтрация ошибок
    vector<string> errors;
    copy_if(logPtr->begin(), logPtr->end(), back_inserter(errors),
        [](const string& log) {
            return log.find("ERROR") != string::npos;
        });

    // Удаление дубликатов
    sort(errors.begin(), errors.end());
    errors.erase(unique(errors.begin(), errors.end()), errors.end());

    // Вывод результатов
    cout << "Исходный журнал:" << endl;
    for (const auto& log : *logPtr) {
        cout << log << endl;
    }

    cout << "\nОшибки:" << endl;
    for (const auto& error : errors) {
        cout << error << endl;
    }

    return 0;
}