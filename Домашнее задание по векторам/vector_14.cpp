#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>

using namespace std;

int main() {
    vector<double> consumption(24);
    setlocale(LC_ALL, "rus");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(100.0, 500.0);

    for (int i = 0; i < 24; i++) {
        consumption[i] = dis(gen);
    }

    double total = accumulate(consumption.begin(), consumption.end(), 0.0);
    cout << "суммарное потребление: " << fixed << setprecision(0) << total << " к¬тЈч" << endl;

    double average = total / consumption.size();
    cout << "среднее потребление: " << fixed << setprecision(1) << average << " к¬тЈч" << endl;

    auto max_it = max_element(consumption.begin(), consumption.end());
    int peak_hour = distance(consumption.begin(), max_it);
    cout << "час пикового потреблени€: " << peak_hour << " (" << *max_it << " к¬тЈч)" << endl;

    vector<double> deviations(24);
    transform(consumption.begin(), consumption.end(), deviations.begin(),
        [average](double value) { return value - average; });

    cout << "отклонени€ от среднего:" << endl;
    for (int i = 0; i < 24; i++) {
        cout << "час " << i << ": " << fixed << setprecision(1) << deviations[i] << " к¬тЈч" << endl;
    }

    vector<double> sorted_consumption = consumption;
    sort(sorted_consumption.begin(), sorted_consumption.end());

    cout << "топ-5 минимальных часов потреблени€:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << sorted_consumption[i] << " к¬тЈч" << endl;
    }

    return 0;
}