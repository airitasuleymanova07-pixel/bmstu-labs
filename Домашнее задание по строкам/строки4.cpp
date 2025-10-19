#include <iostream>
#include <cstring>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char A[MAX_SIZE], B[MAX_SIZE];

    cout << "������� ������ A: ";
    cin.getline(A, MAX_SIZE);

    cout << "������� ������ B: ";
    cin.getline(B, MAX_SIZE);

    bool all_found = true;

    for (int i = 0; B[i] != '\0'; i++) {
        bool found = false;

        for (int j = 0; A[j] != '\0'; j++) {
            if (B[i] == A[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            all_found = false;
            cout << "������ '" << B[i] << "' �� ������ � ������ A" << endl;
            break;
        }
    }

    if (all_found) {
        cout << "��, ��� ������� �� B ���������� � A" << endl;
    }
    else {
        cout << "���, �� ��� ������� �� B ���������� � A" << endl;
    }

    return 0;
}