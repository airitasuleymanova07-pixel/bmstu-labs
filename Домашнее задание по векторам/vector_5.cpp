#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int main() {
    vector<int> numbers(20);
    setlocale(LC_ALL, "rus");
    cout << "введите 20 чисел" << endl;

    for (int i = 0; i < 20; i++) {
        cout << "число " << i + 1 << ": ";
        cin >> numbers[i];
    }
    auto maxElement = max_element(numbers.begin(), numbers.end());
    cout << "максимальный элемент: " << *maxElement << endl;
    auto minElement = min_element(numbers.begin(), numbers.end());
    cout << "минимальный элемент: " << *minElement << endl;
    double average = accumulate(numbers.begin(), numbers.end(), 0.0) / numbers.size();
    cout << "среднее значение: " << average << endl;

    sort(numbers.begin(), numbers.end(), [](int a, int b) {
        return a < b;
        });
    cout << "отсортированный вектор" << endl;
    for (int num : numbers) {
        cout << num << " ";
    }
    cout << "медиана:" << numbers[9] << endl;

    return 0;
}