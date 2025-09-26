#include <iostream>
using namespace std;
int main() {
	int a;
	setlocale(LC_ALL, "rus");
	cout << "¬ведите число ";
	cin >> a;
	if (a % 2 == 0) {
		cout << "„исло " << a << " чЄтное" << endl;
	}
	else {
		cout << "„исло " << a << " нечЄтное" << endl;
	}
	return 0;
}
