#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int n = 15;
    vector<double> A(n);
    setlocale(LC_ALL, "rus");
    cout << "������� 15 ������������ �����:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "������� " << i + 1 << ": ";
        cin >> A[i];
    }

    int min = 0, max = 0;

    for (int i = 1; i < n; i++) {
        if (A[i] < A[min]) {
            min = i;
        }
        if (A[i] > A[max]) {
            max = i;
        }
    }

    cout << "����������� �������: " << A[min] << " (������� " << min + 1 << ")" << endl;
    cout << "������������ �������: " << A[max] << " (������� " << max + 1 << ")" << endl;

    if (min == 1 && max == 0) {
        cout << "������� �����������. ��������� ��� �������� � 2 ����." << endl;

        for (int i = 0; i < n; i++) {
            A[i] = A[i] / 2.0;
        }

        cout << "����� ������:" << endl;
        for (int i = 0; i < n; i++) {
            cout << "A[" << i + 1 << "] = " << A[i] << endl;
        }
    }
    else {
        cout << "������� �� �����������" << endl;
        cout << "������ �������� ��� ���������" << endl;
    }

    return 0;
}
