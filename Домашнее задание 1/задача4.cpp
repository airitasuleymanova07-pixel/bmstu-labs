#include <iostream>
using namespace std;
int main() {
	int a;
	setlocale(LC_ALL, "rus");
	cout << "������� ����� ";
	cin >> a;
	if (a % 2 == 0) {
		cout << "����� " << a << " ������" << endl;
	}
	else {
		cout << "����� " << a << " ��������" << endl;
	}
	return 0;
}
