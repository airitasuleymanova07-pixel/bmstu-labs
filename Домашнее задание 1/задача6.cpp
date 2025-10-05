#include <iostream>
using namespace std;
int main() {
	int age;
	setlocale(LC_ALL, "rus");
	cout << "Введите свой возраст:";
	cin >> age;
	if (age < 18) {
		cout << "Вы подросток" << endl;
	}
	else if (age < 60) {
		cout << "Вы взрослый" << endl;
	}
	else {
		cout << "Вы пенсионер" << endl;
	}
	return 0;
}