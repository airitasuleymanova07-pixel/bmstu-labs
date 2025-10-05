#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    const int n = 15;
    vector<double> numbers(n);
    setlocale(LC_ALL, "rus");
    cout << "������� 15 ������������ �����:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "����� " << i + 1 << ": ";
        cin >> numbers[i];
    }

    int min_pos = 0, max_pos = 0;

    for (int i = 1; i < n; i++) {
        if (numbers[i] < numbers[min_pos]) {
            min_pos = i;
        }
        if (numbers[i] > numbers[max_pos]) {
            max_pos = i;
        }
    }

    cout << "�������� ������������������: ";
    for (int i = 0; i < n; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    swap(numbers[0], numbers[min_pos]);

    if (max_pos == 0) {
        max_pos = min_pos;
    }
    swap(numbers[n - 1], numbers[max_pos]);

    cout << "�������������� ������������������: ";
    for (int i = 0; i < n; i++) {
        cout << numbers[i] << " ";
    }
    cout << endl;

    cout << "����������� ������� (" << numbers[0] << ") ������� � ������" << endl;
    cout << "������������ ������� (" << numbers[n - 1] << ") ������� � ���������" << endl;

    return 0;
}