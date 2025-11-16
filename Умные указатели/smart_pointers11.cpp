#include <iostream>
#include <memory>
#include <vector>
#include <locale>
#include <algorithm>
#include <numeric>
#include <iomanip>
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    vector<double> signals = { 25.4, 27.1, 30.0, 29.5, 28.3 };

    // Создание динамического массива
    auto signalPtr = make_unique<double[]>(signals.size());
    copy(signals.begin(), signals.end(), signalPtr.get());

    // Лямбда-функции
    auto mean = [](const unique_ptr<double[]>& arr, int size) -> double {
        double sum = 0;
        for (int i = 0; i < size; i++) {
            sum += arr[i];
        }
        return sum / size;
        };

    auto normalize = [](unique_ptr<double[]>& arr, int size, double maxVal) {
        for (int i = 0; i < size; i++) {
            arr[i] /= maxVal;
        }
        };

    auto copyBack = [](unique_ptr<double[]>& source, vector<double>& dest, int size) {
        dest.clear();
        for (int i = 0; i < size; i++) {
            dest.push_back(source[i]);
        }
        };

    // Вычисления
    cout << "Исходные данные: ";
    for (auto val : signals) {
        cout << val << " ";
    }
    cout << endl;

    double avg = mean(signalPtr, signals.size());
    cout << "Среднее значение: " << avg << endl;

    double maxSignal = *max_element(signals.begin(), signals.end());
    normalize(signalPtr, signals.size(), maxSignal);

    copyBack(signalPtr, signals, signals.size());

    cout << "Нормализованные сигналы: ";
    for (auto val : signals) {
        cout << fixed << setprecision(3) << val << " ";
    }
    cout << endl;

    return 0;
}