#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int>number(10);
	setlocale(LC_ALL, "rus");
	for (int i = 0; i < 10; i++) { //����, ���� ��������� ������ ������� 
		numbers[i] = i + 1;
	}

	cout << "�������� �������:";
	for_each(numbers.begin(), numbers.end(), [](int n) {
		cout << n << endl;
		});
	return 0;
}