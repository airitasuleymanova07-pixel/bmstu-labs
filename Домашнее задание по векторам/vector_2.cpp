#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> numbers(10);
    setlocale(LC_ALL, "rus");
    cout << "¬ведите 10 чисел:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "„исло " << i + 1 << ": ";
        cin >> numbers[i];
    }
    for_each(numbers.begin(), numbers.end(), [](int& n) {
        n *= 2;
        });
    cout << "„исла, умноженные на 2: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        cout << n << " ";
        });
    cout << endl;

    return 0;
}