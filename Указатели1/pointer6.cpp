#include <iostream>
#include <cstring>

using namespace std;

void reverse(char* str) {
	if (str == nullptr || *str == '\0') {
		return;
	}

	char* start = str;
	char* end = str;

	while (*end != '\0') {
		end++;
	}
	end--;

	while (start < end) {
		char temp = *start;
		*start = *end;
		*end = temp;

		start++;
		end--;
	}
}
int main() {
	const int max_size = 100;
	char string[max_size];
	setlocale(LC_ALL, "rus");
	cout << "Введите строку:";
	cin.getline(string, max_size);

	reverse(string);

	cout << "Перевернутая строка:" << string << endl;
	return 0;
}
