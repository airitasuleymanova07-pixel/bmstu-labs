#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    vector<double> temperatures;
    setlocale(LC_ALL, "rus");

    int n;
    cout << "������� ���������� ����������: ";
    cin >> n;
    cout << "������� " << n << " ����������:" << endl;
    for (int i = 0; i < n; i++) {
        double temp;
        cout << "����������� " << i + 1 << ": ";
        cin >> temp;
        temperatures.push_back(temp);
    }

    cout << "�������� �����������: ";
    for (double temp : temperatures) {
        cout << temp << " ";
    }
    cout << endl;

    temperatures.erase(
        remove_if(temperatures.begin(), temperatures.end(),
            [](double temp) {
                return temp < -50 || temp > 50;
            }),
        temperatures.end()
    );

    cout << "����������� � ��������� [-50, 50]: ";
    for (double temp : temperatures) {
        cout << temp << " ";
    }
    cout << endl;

    if (temperatures.empty()) {
        cout << "����� ���������� �� �������� ����������!" << endl;
        return 0;
    }

    auto min_temp = min_element(temperatures.begin(), temperatures.end());
    cout << "����������� �����������: " << *min_temp << endl;

    auto max_temp = max_element(temperatures.begin(), temperatures.end());
    cout << "������������ �����������: " << *max_temp << endl;

    double average = accumulate(temperatures.begin(), temperatures.end(), 0.0)
        / temperatures.size();
    cout << "������� �����������: " << average << endl;

    bool all_above_minus_10 = all_of(temperatures.begin(), temperatures.end(),
        [](double temp) {
            return temp > -10;
        });

    if (all_above_minus_10) {
        cout << "��� ����������� ��������� -10 ��������" << endl;
    }
    else {
        cout << "�����������, ������� ��������� -10 ��������" << endl;
        for (double temp : temperatures) {
            if (temp <= -10) {
                cout << temp << " ";
            }
        }
        cout << endl;
    }

    return 0;
}