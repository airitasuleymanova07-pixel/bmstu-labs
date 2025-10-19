#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

int main() {
    vector<double> consumption(30);
    setlocale(LC_ALL, "rus");

    cout << "¬ведите потребление энергии за 30 дней (к¬тЈч):" << endl;
    for (int i = 0; i < 30; i++) {
        cout << "ƒень " << i + 1 << ": ";
        cin >> consumption[i];
    }

    double total = accumulate(consumption.begin(), consumption.end(), 0.0);
    cout << "1. ќбщее потребление за мес€ц: " << fixed << setprecision(1) << total << " к¬тЈч" << endl;

    double average = total / consumption.size();
    cout << "2. —реднесуточное потребление: " << fixed << setprecision(1) << average << " к¬тЈч" << endl;

    auto min_it = min_element(consumption.begin(), consumption.end());
    auto max_it = max_element(consumption.begin(), consumption.end());

    int min_day = distance(consumption.begin(), min_it) + 1;
    int max_day = distance(consumption.begin(), max_it) + 1;

    cout << "3. ƒень с минимальным потреблением: " << min_day << " (" << *min_it << " к¬тЈч)" << endl;
    cout << "   ƒень с максимальным потреблением: " << max_day << " (" << *max_it << " к¬тЈч)" << endl;

    double threshold = average * 1.2;
    vector<int> peaks;

    for (int i = 0; i < consumption.size(); i++) {
        if (consumption[i] > threshold) {
            peaks.push_back(i + 1);
        }
    }
    cout << "4. ѕиковые дни (> " << fixed << setprecision(1) << threshold << " к¬тЈч): ";
    if (!peaks.empty()) {
        for (int day : peaks) {
            cout << day << " ";
        }
        cout << "(" << peaks.size() << " дней)" << endl;
    }
    else {
        cout << "нет" << endl;
    }

    return 0;
}