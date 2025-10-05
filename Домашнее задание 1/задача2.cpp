#include <iostream>
using namespace std;
int main() {
	int a;
	setlocale(LC_ALL, "rus");
	cout << "Ширина: ";
	cin >> a;
	int b;
	cout << "Высота:";
	cin >> b;
	int s = a * b;	
	cout << "Площадь:" << s << endl;
	return 0;
}