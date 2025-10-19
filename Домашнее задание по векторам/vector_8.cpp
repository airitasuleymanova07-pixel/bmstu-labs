#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <random>

using namespace std;

int main() {
    vector<int> speeds(50);
    setlocale(LC_ALL, "rus");

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 180);

    for (int i = 0; i < 50; i++) {
        speeds[i] = dis(gen);
    }

    cout << "�������� �������� (50 ��������):" << endl;
    for (int i = 0; i < speeds.size(); i++) {
        cout << speeds[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << endl;

    vector<int> speeding;
    copy_if(speeds.begin(), speeds.end(), back_inserter(speeding),
        [](int speed) { return speed > 120; });
    cout << "���������� �������� (>120 ��/�): " << speeding.size() << " �������" << endl;
    cout << "��������: ";
    for (int speed : speeding) {
        cout << speed << " ";
    }
    cout << endl << endl;

    double average_speed = accumulate(speeds.begin(), speeds.end(), 0.0) / speeds.size();
    cout << "������� ��������: " << average_speed << " ��/�" << endl;

    bool always_moving = all_of(speeds.begin(), speeds.end(),
        [](int speed) { return speed > 0; });

    if (always_moving) {
        cout << "���������� ������ �������� (��� �������� > 0)" << endl;
    }
    else {
        cout << "���������� �� ������ �������� (���� ���������)" << endl;

        vector<int> stops;
        copy_if(speeds.begin(), speeds.end(), back_inserter(stops),
            [](int speed) { return speed == 0; });

        cout << "��������� (�������� = 0): " << stops.size() << " �������" << endl;
    }
    cout << endl;
    vector<int> sorted_speeds = speeds;
    sort(sorted_speeds.begin(), sorted_speeds.end(), greater<int>());

    cout << "10 ������������ ���������:" << endl;
    for (int i = 0; i < min(10, (int)sorted_speeds.size()); i++) {
        cout << i + 1 << ". " << sorted_speeds[i] << " ��/�" << endl;
    }

    return 0;
}