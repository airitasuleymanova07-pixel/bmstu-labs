#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <locale.h>
#include <iomanip>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    ifstream inputFile("vibration_log.txt");

    if (!inputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл vibration_log.txt" << endl;
        return 1;
    }

    vector<double> amplitudes;
    double value;

    while (inputFile >> value) {
        amplitudes.push_back(value);
    }

    inputFile.close();

    int totalMeasurements = amplitudes.size();

    auto filterAbove005 = [](double x) { return x > 0.05; };
    vector<double> filteredAmplitudes;
    copy_if(amplitudes.begin(), amplitudes.end(),
        back_inserter(filteredAmplitudes), filterAbove005);

    double sumAll = accumulate(amplitudes.begin(), amplitudes.end(), 0.0);
    double averageAll = sumAll / totalMeasurements;

    double minValue = *min_element(filteredAmplitudes.begin(), filteredAmplitudes.end());
    double maxValue = *max_element(filteredAmplitudes.begin(), filteredAmplitudes.end());

    ofstream reportFile("vibration_report.txt");

    if (!reportFile.is_open()) {
        cout << "Ошибка: не удалось создать файл vibration_report.txt" << endl;
        return 1;
    }

    reportFile << fixed << setprecision(4);
    reportFile << "Количество измерений: " << totalMeasurements << endl;
    reportFile << "Фильтрованные значения (>0.05): ";

    for (size_t i = 0; i < filteredAmplitudes.size(); i++) {
        reportFile << filteredAmplitudes[i];
        if (i < filteredAmplitudes.size() - 1) {
            reportFile << " ";
        }
    }

    reportFile << endl;
    reportFile << "Среднее значение: " << averageAll << endl;
    reportFile << "Минимум: " << minValue << endl;
    reportFile << "Максимум: " << maxValue << endl;

    reportFile.close();

    cout << "Анализ вибрационных данных завершён. Отчёт сохранён в vibration_report.txt" << endl;

    return 0;
}