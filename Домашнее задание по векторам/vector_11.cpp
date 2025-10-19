#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iomanip>
#include <numeric>

using namespace std;

int main() {
    vector<double> amplitude(50);
    setlocale(LC_ALL, "rus");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 5.0);

    for (int i = 0; i < 50; i++) {
        amplitude[i] = dis(gen);
    }

    cout << "Всего измерений: " << amplitude.size() << endl;
    cout << "Первые 10 значений: ";
    for (int i = 0; i < 10; i++) {
        cout << fixed << setprecision(2) << amplitude[i] << " ";
    }
    cout << "..." << endl << endl;

    int initial_size = amplitude.size();
    amplitude.erase(
        remove_if(amplitude.begin(), amplitude.end(),
            [](double n) { return n < 0.1; }),
        amplitude.end()
    );
    int removed_count = initial_size - amplitude.size();

    cout << "Удалено значений : " << removed_count << endl;
    cout << "Осталось значений : " << amplitude.size() << endl;

    if (amplitude.empty()) {
        cout << "Нет данных для анализа!" << endl;
        return 0;
    }

    double average = accumulate(amplitude.begin(), amplitude.end(), 0.0) / amplitude.size();
    cout << "Среднее значение:" << fixed << setprecision(2) << average << endl;

    auto max_it = max_element(amplitude.begin(), amplitude.end());
    cout << "Максимальное значение: " << fixed << setprecision(2) << *max_it << endl;

    bool all_above_threshold = all_of(amplitude.begin(), amplitude.end(),
        [](double n) { return n > 0.5; });

    cout << "Проверка порога 0.5:" << endl;
    if (all_above_threshold) {
        cout << "Все значения превышают порог 0.5" << endl;
    }
    else {
        cout << "Не все значения превышают порог 0.5" << endl;

        int below_threshold = count_if(amplitude.begin(), amplitude.end(),
            [](double n) { return n <= 0.5; });
        cout << "Значений меньше или равно 0.5: " << below_threshold << endl;
    }

    vector<double> sorted_amplitude = amplitude;
    sort(sorted_amplitude.begin(), sorted_amplitude.end(), greater<double>());

    cout << "Наибольших амплитуд" << endl;
    int count = min(10, (int)sorted_amplitude.size());
    for (int i = 0; i < count; i++) {
        cout << "   " << i + 1 << ". " << fixed << setprecision(2) << sorted_amplitude[i] << endl;
    }

    return 0;
}