#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> numbers(20);
    setlocale(LC_ALL, "rus");
    cout << "������� 20 �����" << endl;

    for (int i = 0; i < 20; i++) {
        cout << "����� " << i + 1 << ": ";
        cin >> numbers[i];
    }

    cout << "����� 7 ������� �� ��������: ";
    bool found = false;
    auto it = numbers.begin();

    while ((it = find(it, numbers.end(), 7)) != numbers.end()) {
        int position = distance(numbers.begin(), it);
        cout << position << " ";
        found = true;
        it++; 
    }

    if (!found) {
        cout << "����� 7 �� �������";
    }
    cout << endl;

    sort(numbers.begin(), numbers.end());
    cout << "��������������� ������: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    auto last = unique(numbers.begin(), numbers.end());
    numbers.erase(last, numbers.end());

    cout << "������ ��� ������������� �����: ";
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}