#include <iostream>
using namespace std;
int main() {
	int age;
	setlocale(LC_ALL, "rus");
	cout << "������� ���� �������:";
	cin >> age;
	if (age < 18) {
		cout << "�� ���������" << endl;
	}
	else if (age < 60) {
		cout << "�� ��������" << endl;
	}
	else {
		cout << "�� ���������" << endl;
	}
	return 0;
}