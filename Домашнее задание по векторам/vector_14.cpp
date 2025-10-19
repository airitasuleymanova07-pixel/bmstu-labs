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
    cout << "��������� �����������: " << fixed << setprecision(0) << total << " ����" << endl;

    double average = total / consumption.size();
    cout << "������� �����������: " << fixed << setprecision(1) << average << " ����" << endl;

    auto max_it = max_element(consumption.begin(), consumption.end());
    int peak_hour = distance(consumption.begin(), max_it);
    cout << "��� �������� �����������: " << peak_hour << " (" << *max_it << " ����)" << endl;

    vector<double> deviations(24);
    transform(consumption.begin(), consumption.end(), deviations.begin(),
        [average](double value) { return value - average; });

    cout << "���������� �� ��������:" << endl;
    for (int i = 0; i < 24; i++) {
        cout << "��� " << i << ": " << fixed << setprecision(1) << deviations[i] << " ����" << endl;
    }

    vector<double> sorted_consumption = consumption;
    sort(sorted_consumption.begin(), sorted_consumption.end());

    cout << "���-5 ����������� ����� �����������:" << endl;
    for (int i = 0; i < 5; i++) {
        cout << sorted_consumption[i] << " ����" << endl;
    }

    return 0;
}