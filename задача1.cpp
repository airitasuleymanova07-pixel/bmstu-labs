#include <iostream>
using namespace std;
int main() {
	int s;
	setlocale(LC_ALL, "rus");
	cout << "������� ����������:";
	cin >> s;
	int m = s / 100;
	int c = s % 100;
	cout << "�����:" << m << endl;
	cout << "���������� ����������:" << c << endl;
	return 0;
}