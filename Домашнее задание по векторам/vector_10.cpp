#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

int main() {
    vector<double> consumption(30);
    setlocale(LC_ALL, "rus");

    cout << "������� ����������� ������� �� 30 ���� (����):" << endl;
    for (int i = 0; i < 30; i++) {
        cout << "���� " << i + 1 << ": ";
        cin >> consumption[i];
    }

    double total = accumulate(consumption.begin(), consumption.end(), 0.0);
    cout << "1. ����� ����������� �� �����: " << fixed << setprecision(1) << total << " ����" << endl;

    double average = total / consumption.size();
    cout << "2. �������������� �����������: " << fixed << setprecision(1) << average << " ����" << endl;

    auto min_it = min_element(consumption.begin(), consumption.end());
    auto max_it = max_element(consumption.begin(), consumption.end());

    int min_day = distance(consumption.begin(), min_it) + 1;
    int max_day = distance(consumption.begin(), max_it) + 1;

    cout << "3. ���� � ����������� ������������: " << min_day << " (" << *min_it << " ����)" << endl;
    cout << "   ���� � ������������ ������������: " << max_day << " (" << *max_it << " ����)" << endl;

    double threshold = average * 1.2;
    vector<int> peaks;

    for (int i = 0; i < consumption.size(); i++) {
        if (consumption[i] > threshold) {
            peaks.push_back(i + 1);
        }
    }
    cout << "4. ������� ��� (> " << fixed << setprecision(1) << threshold << " ����): ";
    if (!peaks.empty()) {
        for (int day : peaks) {
            cout << day << " ";
        }
        cout << "(" << peaks.size() << " ����)" << endl;
    }
    else {
        cout << "���" << endl;
    }

    return 0;
}