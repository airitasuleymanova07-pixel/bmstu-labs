#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <numeric>
#include <locale.h>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    ifstream inputFile("power_log.txt");

    if (!inputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл power_log.txt" << endl;
        return 1;
    }

    map<string, vector<double>> deviceData;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string timestamp, device;
        double power;

        if (ss >> timestamp >> device >> power) {
            deviceData[device].push_back(power);
        }
    }

    inputFile.close();

    ofstream reportFile("energy_report.txt");

    if (!reportFile.is_open()) {
        cout << "Ошибка: не удалось создать файл energy_report.txt" << endl;
        return 1;
    }

    reportFile << fixed << setprecision(2);

    for (const auto& entry : deviceData) {
        const string& device = entry.first;
        const vector<double>& powers = entry.second;

        if (!powers.empty()) {
            int measurements = powers.size();
            double total = accumulate(powers.begin(), powers.end(), 0.0);
            double average = total / measurements;

            reportFile << device << ": measurements = " << measurements
                << ", total = " << total << " kWh"
                << ", average = " << average << " kW" << endl;
        }
    }

    reportFile.close();

    cout << "Анализ завершён. Результаты сохранены в energy_report.txt" << endl;

    return 0;
}