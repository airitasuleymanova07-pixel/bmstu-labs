#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int size;
    setlocale(LC_ALL, "rus");
    cout << "Введите количество чисел: ";
    cin >> size;

    vector<int> numbers(size);

    cout << "Введите " << size << " чисел:" << endl;
    for (int i = 0; i < size; i++) {
        cout << "Число " << i + 1 << ": ";
        cin >> numbers[i];
    }

    cout << "Исходный вектор: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;

    auto new_end = remove_if(numbers.begin(), numbers.end(), [](int n) {
        return n < 0;
        });
    numbers.erase(new_end, numbers.end());

    cout << "После удаления отрицательных чисел: ";
    for (int n : numbers) {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}