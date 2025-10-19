#include <iostream> 
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int>numbers(20);
	setlocale(LC_ALL, "rus");
	cout << "Введите 20 чисел:" << endl;

	for (int i = 0; i < 20; i++) {
		cout << "Число " << i + 1 << ": ";
		cin >> numbers[i];
	}
	vector<int>::iterator maxElement = max_element(numbers.begin(), numbers.end(),
		[](int a, int b) {
			return a < b;
		}
	);
	cout << "Максимальный элемент:" << *maxElement;
	return 0;
}