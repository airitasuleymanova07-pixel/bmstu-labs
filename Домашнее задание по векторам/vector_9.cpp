#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

int main() {
    vector<double> power(20);
    setlocale(LC_ALL, "rus");

    cout << "������� 20 ��������� �������� ��������� (���):" << endl;
    for (int i = 0; i < 20; i++) {
        cout << "��������� " << i + 1 << ": ";
        cin >> power[i];
    }

    cout << "������ �������� ���������" << endl;

    power.erase(
        remove_if(power.begin(), power.end(), [](double p) { return p < 0; }),
        power.end()
    );

    cout << "���������� ���������: " << power.size() << endl;

    if (power.empty()) {
        cout << "��� ������ ��� �������!" << endl;
        return 0;
    }

    auto min_it = min_element(power.begin(), power.end());
    auto max_it = max_element(power.begin(), power.end());
    double avg = accumulate(power.begin(), power.end(), 0.0) / power.size();

    cout << fixed << setprecision(1);
    cout << "���: " << *min_it << " ���, ����: " << *max_it << " ���, �����: " << avg << " ���" << endl;

    bool in_range = all_of(power.begin(), power.end(),
        [](double p) { return p >= 10 && p <= 90; });
    cout << "� ��������� 10-90 ���: " << (in_range ? "��" : "���") << endl;

    sort(power.begin(), power.end());
    double median = power.size() % 2 == 0 ?
        (power[power.size() / 2 - 1] + power[power.size() / 2]) / 2.0 :
        power[power.size() / 2];

    cout << "�������: " << median << " ���" << endl;

    return 0;
}