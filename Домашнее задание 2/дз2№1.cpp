#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n;
    setlocale(LC_ALL, "rus");
    cout << "������� ���������� ����� n: ";
    cin >> n;

    vector<int> A(n + 1); 

    cout << "������� " << n << " ����������� �����: ";
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    int count = 0;
    cout << "�������� ������� Ak > 2^k:" << endl;
    for (int k = 1; k <= n; k++) {
        int power = pow(2, k);
        if (A[k] > power) {
            count++;
        cout << "A" << k << " = " << A[k] << " > 2^" << k << " = " << power << endl;
    }

    cout << "���������� ������, ��������������� ������� Ak > 2^k: " << count << endl;

    return 0;
}