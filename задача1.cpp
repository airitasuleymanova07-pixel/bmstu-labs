#include <iostream>
using namespace std;
int main() {
	int s;
	setlocale(LC_ALL, "rus");
	cout << "Введите сантиметры:";
	cin >> s;
	int m = s / 100;
	int c = s % 100;
	cout << "Метры:" << m << endl;
	cout << "Оставшиеся сантиметры:" << c << endl;
	return 0;
}