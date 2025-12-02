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

    ifstream sensorFile("sensor_data.txt");

    if (!sensorFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл sensor_data.txt" << endl;
        return 1;
    }

    vector<double> temperatures;
    vector<double> filteredTemperatures;
    double value;

    cout << "Исходные данные с датчиков:" << endl;

    while (sensorFile >> value) {
        temperatures.push_back(value);
        cout << value << " ";
    }

    sensorFile.close();

    auto validRangeFilter = [](double temp) {
        return temp >= -50.0 && temp <= 50.0;
        };

    copy_if(temperatures.begin(), temperatures.end(),
        back_inserter(filteredTemperatures), validRangeFilter);

    ofstream filteredFile("filtered_sensor_data.txt");

    if (!filteredFile.is_open()) {
        cout << "Ошибка: не удалось создать файл filtered_sensor_data.txt" << endl;
        return 1;
    }

    filteredFile << "Отфильтрованные данные (диапазон -50°C до +50°C):" << endl;
    filteredFile << "==================================================" << endl;

    for (const auto& temp : filteredTemperatures) {
        filteredFile << fixed << setprecision(1) << temp << endl;
    }

    filteredFile.close();

    if (!filteredTemperatures.empty()) {
        double sum = accumulate(filteredTemperatures.begin(), filteredTemperatures.end(), 0.0);
        double average = sum / filteredTemperatures.size();

        cout << endl << endl << "Результаты обработки:" << endl;
        cout << "=======================" << endl;
        cout << "Всего измерений: " << temperatures.size() << endl;
        cout << "Валидных измерений: " << filteredTemperatures.size() << endl;
        cout << "Некорректных измерений: " << temperatures.size() - filteredTemperatures.size() << endl;
        cout << "Средняя температура: " << fixed << setprecision(1) << average << "°C" << endl;
        cout << "Отфильтрованные данные сохранены в filtered_sensor_data.txt" << endl;
    }
    else {
        cout << endl << "Нет валидных данных в указанном диапазоне!" << endl;
    }

    return 0;
}