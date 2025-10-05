#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

int main() {
    int n;
    setlocale(LC_ALL, "rus");
    cout << "Введите количество чисел n: ";
    cin >> n;

    vector<int> A(n + 1); 

    cout << "Введите " << n << " натуральных чисел: ";
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
    }
    int count = 0;
    cout << "Проверка условия Ak > 2^k:" << endl;
    for (int k = 1; k <= n; k++) {
        int power = pow(2, k);
        if (A[k] > power) {
            count++;
        cout << "A" << k << " = " << A[k] << " > 2^" << k << " = " << power << endl;
    }

    cout << "Количество членов, удовлетворяющих условию Ak > 2^k: " << count << endl;

    return 0;
}