#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <locale.h>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    ifstream inputFile("temperature_data.txt");

    if (!inputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл temperature_data.txt" << endl;
        return 1;
    }

    map<string, vector<double>> sensorData;
    string line;

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string sensor;
        double temperature;

        if (ss >> sensor >> temperature) {
            sensorData[sensor].push_back(temperature);
        }
    }

    inputFile.close();

    ofstream reportFile("report.txt");

    if (!reportFile.is_open()) {
        cout << "Ошибка: не удалось создать файл report.txt" << endl;
        return 1;
    }

    reportFile << fixed << setprecision(1);

    for (const auto& entry : sensorData) {
        const string& sensor = entry.first;
        const vector<double>& temps = entry.second;

        if (!temps.empty()) {
            double minTemp = *min_element(temps.begin(), temps.end());
            double maxTemp = *max_element(temps.begin(), temps.end());
            double sum = accumulate(temps.begin(), temps.end(), 0.0);
            double avgTemp = sum / temps.size();

            reportFile << sensor << ": min = " << minTemp
                << ", max = " << maxTemp
                << ", avg = " << avgTemp << endl;
        }
    }

    reportFile.close();

    cout << "Отчёт о температурных данных сохранён в report.txt" << endl;

    return 0;
}