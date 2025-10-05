#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n;
    setlocale(LC_ALL, "rus");
    cout << "Введите количество чисел n: ";
    cin >> n;

    vector<int> A(n + 1);

    cout << "Введите " << n << " натуральных и целых чисел: ";
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }

    int count = 0;
    for (int k = 1; k <= n; k++) {
        if (A[k] % 2 == 0) {
            count++;
        }
    }
    cout << "Количество четных чисел: " << count << endl;

    sort(A.begin() + 1, A.end());

    cout << "Отсортированный массив: ";
    for (int i = 1; i <= n; i++) {
        cout << A[i] << " ";
    }
    cout << endl;
    int max = -1;
    for (int i = 1; i <= n; i++) {
        if (A[i] % 2 != 0 && A[i] > max) {
            max = A[i];
        }
    }

    if (max != -1) {
        cout << "Наибольшее нечетное число: " << max << endl;
    }
    else {
        cout << "Нечетных чисел нет" << endl;
    }
    return 0;
}