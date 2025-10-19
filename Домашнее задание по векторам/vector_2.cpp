#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> numbers(10);
    setlocale(LC_ALL, "rus");
    cout << "������� 10 �����:" << endl;
    for (int i = 0; i < 10; i++) {
        cout << "����� " << i + 1 << ": ";
        cin >> numbers[i];
    }
    for_each(numbers.begin(), numbers.end(), [](int& n) {
        n *= 2;
        });
    cout << "�����, ���������� �� 2: ";
    for_each(numbers.begin(), numbers.end(), [](int n) {
        cout << n << " ";
        });
    cout << endl;

    return 0;
}