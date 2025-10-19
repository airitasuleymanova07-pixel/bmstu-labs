#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

int main() {
    vector<double> power(20);
    setlocale(LC_ALL, "rus");

    cout << "Введите 20 измерений мощности двигателя (кВт):" << endl;
    for (int i = 0; i < 20; i++) {
        cout << "Измерение " << i + 1 << ": ";
        cin >> power[i];
    }

    cout << "АНАЛИЗ МОЩНОСТИ ДВИГАТЕЛЯ" << endl;

    power.erase(
        remove_if(power.begin(), power.end(), [](double p) { return p < 0; }),
        power.end()
    );

    cout << "Корректных измерений: " << power.size() << endl;

    if (power.empty()) {
        cout << "Нет данных для анализа!" << endl;
        return 0;
    }

    auto min_it = min_element(power.begin(), power.end());
    auto max_it = max_element(power.begin(), power.end());
    double avg = accumulate(power.begin(), power.end(), 0.0) / power.size();

    cout << fixed << setprecision(1);
    cout << "Мин: " << *min_it << " кВт, Макс: " << *max_it << " кВт, Средн: " << avg << " кВт" << endl;

    bool in_range = all_of(power.begin(), power.end(),
        [](double p) { return p >= 10 && p <= 90; });
    cout << "В диапазоне 10-90 кВт: " << (in_range ? "Да" : "Нет") << endl;

    sort(power.begin(), power.end());
    double median = power.size() % 2 == 0 ?
        (power[power.size() / 2 - 1] + power[power.size() / 2]) / 2.0 :
        power[power.size() / 2];

    cout << "Медиана: " << median << " кВт" << endl;

    return 0;
}