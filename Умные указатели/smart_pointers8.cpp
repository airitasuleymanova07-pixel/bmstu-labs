#include <iostream>
#include <memory>
#include <locale>
#include <iomanip>
using namespace std;

double calculateAverage(const unique_ptr<double[]>& arr, int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    return sum / size;
}

int main() {
    setlocale(LC_ALL, "rus");

    const int size = 5;

    // Создание массивов
    auto temperatures = make_unique<double[]>(size);
    auto pressures = make_unique<double[]>(size);
    auto humidity = make_unique<double[]>(size);

    // Заполнение данными
    double tempData[] = { 20.5, 22.1, 19.8, 23.4, 21.7 };
    double pressData[] = { 1013.2, 1012.8, 1014.1, 1011.9, 1013.5 };
    double humData[] = { 65.0, 68.2, 62.1, 70.5, 67.3 };

    for (int i = 0; i < size; i++) {
        temperatures[i] = tempData[i];
        pressures[i] = pressData[i];
        humidity[i] = humData[i];
    }

    // Вычисление средних значений
    double avgTemp = calculateAverage(temperatures, size);
    double avgPress = calculateAverage(pressures, size);
    double avgHum = calculateAverage(humidity, size);

    // Вывод результатов
    cout << "| Параметр    | Среднее значение |" << endl;
    cout << "|-------------|------------------|" << endl;
    cout << "| Температура | " << setw(8) << avgTemp << " °C     |" << endl;
    cout << "| Давление    | " << setw(8) << avgPress << " hPa  |" << endl;
    cout << "| Влажность   | " << setw(8) << avgHum << " %     |" << endl;

    return 0;
}