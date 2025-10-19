#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>
#include <iomanip>

using namespace std;

int main() {
    vector<double> pressure(50);
    setlocale(LC_ALL, "rus");

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(1.0, 10.0);

    for (int i = 0; i < 50; i++) {
        pressure[i] = dis(gen);
    }

    pressure.erase(
        remove_if(pressure.begin(), pressure.end(),
            [](double p) { return p < 0 || p > 12; }),
        pressure.end()
    );

    if (pressure.empty()) {
        cout << "��� ���������� ������ ��� �������" << endl;
        return 0;
    }
    double average_pressure = accumulate(pressure.begin(), pressure.end(), 0.0) / pressure.size();
    cout << "������� ��������: " << fixed << setprecision(2) << average_pressure << " ���" << endl;

    auto min_it = min_element(pressure.begin(), pressure.end());
    auto max_it = max_element(pressure.begin(), pressure.end());

    cout << "�����������: " << fixed << setprecision(1) << *min_it << " ���" << endl;
    cout << "������������: " << fixed << setprecision(1) << *max_it << " ���" << endl;

    cout << "�������� ���� 8 ���:" << endl;
    for_each(pressure.begin(), pressure.end(), [](double p) {
        if (p > 8.0) {
            cout << fixed << setprecision(1) << p << " ���" << endl;
        }
        });

    return 0;
}