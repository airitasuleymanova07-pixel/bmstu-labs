#include <iostream>
#include <cstring>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	const int max_size = 100;
	char string[max_size];

	cout << "Введите строки:";
	cin.getline(string, max_size);

	cout << "Исходная строка:" << string << endl;

	char* ptr = string;
	while (*ptr) {
		if (*ptr == ' ') *ptr = '_';
		ptr++;
	}
	cout << "Итог:" << string << endl;
	return 0;

}