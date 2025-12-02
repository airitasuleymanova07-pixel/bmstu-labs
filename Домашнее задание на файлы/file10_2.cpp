#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <locale.h>

using namespace std;

void createConfig() {
    ofstream file("config.json");

    if (!file.is_open()) {
        cout << "Ошибка: не удалось создать файл config.json" << endl;
        return;
    }

    file << "{\n";
    file << "  \"app_name\": \"My Application\",\n";
    file << "  \"version\": \"1.0.0\",\n";
    file << "  \"settings\": {\n";
    file << "    \"max_connections\": 100,\n";
    file << "    \"timeout\": 30,\n";
    file << "    \"debug_mode\": true\n";
    file << "  },\n";
    file << "  \"database\": {\n";
    file << "    \"host\": \"localhost\",\n";
    file << "    \"port\": 5432,\n";
    file << "    \"username\": \"admin\"\n";
    file << "  }\n";
    file << "}\n";

    file.close();
    cout << "Конфигурационный файл создан" << endl;
}

void readConfig() {
    ifstream file("config.json");

    if (!file.is_open()) {
        cout << "Ошибка: не удалось открыть файл config.json" << endl;
        return;
    }

    cout << "\nСодержимое config.json:" << endl;
    cout << "========================" << endl;

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();
}

void modifyConfig() {
    ifstream inFile("config.json");

    if (!inFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл config.json" << endl;
        return;
    }

    vector<string> lines;
    string line;

    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();

    string searchKey = "\"timeout\":";
    for (size_t i = 0; i < lines.size(); i++) {
        size_t pos = lines[i].find(searchKey);
        if (pos != string::npos) {
            size_t valueStart = pos + searchKey.length();
            size_t valueEnd = lines[i].find(",", valueStart);

            if (valueEnd == string::npos) {
                valueEnd = lines[i].find("}", valueStart);
            }

            if (valueEnd != string::npos) {
                int newValue;
                cout << "Текущее значение timeout: "
                    << lines[i].substr(valueStart, valueEnd - valueStart) << endl;
                cout << "Введите новое значение для timeout: ";
                cin >> newValue;

                lines[i].replace(valueStart, valueEnd - valueStart, " " + to_string(newValue));
                cout << "Значение изменено" << endl;
                break;
            }
        }
    }

    ofstream outFile("config.json");
    for (const auto& l : lines) {
        outFile << l << endl;
    }

    outFile.close();
}

int main() {
    setlocale(LC_ALL, "rus");

    int choice;

    while (true) {
        cout << "\nМеню работы с конфигурацией:" << endl;
        cout << "1. Создать конфигурационный файл" << endl;
        cout << "2. Просмотреть конфигурационный файл" << endl;
        cout << "3. Изменить параметр timeout" << endl;
        cout << "4. Выход" << endl;
        cout << "Введите номер: ";
        cin >> choice;

        switch (choice) {
        case 1:
            createConfig();
            break;
        case 2:
            readConfig();
            break;
        case 3:
            modifyConfig();
            break;
        case 4:
            return 0;
        default:
            cout << "Неверный выбор!" << endl;
        }
    }

    return 0;
}