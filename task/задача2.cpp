#include <iostream>
using namespace std;
int main() {
	int a;
	setlocale(LC_ALL, "rus");
	cout << "������: ";
	cin >> a;
	int b;
	cout << "������:";
	cin >> b;
	int s = a * b;	
	cout << "�������:" << s << endl;
	return 0;
}