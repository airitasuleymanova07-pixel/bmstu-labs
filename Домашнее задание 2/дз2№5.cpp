#include <iostream>
#include <vector>

using namespace std;

int main() {
    const int n = 10;
    vector <int> A(n);
    setlocale(LC_ALL, "rus");
    cout << "������� 10 �����:" << endl;


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

    if (min == 4 && max == 9) {
        cout << "������� ��������������:" << (A[max] + A[min]) / 2 << endl;
    }
    else {
        cout << "������� �������������� �� �������" << endl;
    }
    return 0;
}