#include <iostream>
using namespace std;

int main() {
    int num;
    setlocale(LC_ALL, "rus");
    cout << "������� ����� �����: ";
    cin >> num;
    if (num % 3 == 0 && num % 5 == 0) {
        cout << "����� ������� �� 3 � 5 ������������." << endl;
    }
    else if (num % 3 == 0) {
        cout << "����� ������� ������ �� 3." << endl;
    }
    else if (num % 5 == 0) {
        cout << "����� ������� ������ �� 5." << endl;
    }
    else {
        cout << "����� �� ������� �� �� 3, �� �� 5." << endl;
    }
    return 0;
}