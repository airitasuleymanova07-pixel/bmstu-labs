#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int>numbers(20);
	setlocale(LC_ALL, "rus");
	cout << "������� 20 �����:" << endl;

	for (int i = 0; i < 20; i++) {
		cout << "����� " << i + 1 << ": ";
		cin >> numbers[i];
	}
	vector<int>::iterator maxElement = max_element(numbers.begin(), numbers.end(),
		[](int a, int b) {
			return a < b;
		}
	);
	cout << "������������ �������:" << *maxElement;
	return 0;
}