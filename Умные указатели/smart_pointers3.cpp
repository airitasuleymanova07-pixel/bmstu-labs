#include <iostream>
#include <memory>
#include <locale>
using namespace std;

void fillArray(unique_ptr<int[]>& arr, int n) {
    for (int i = 0; i < n; i++) {
        arr[i] = i * i;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    int n = 5;
    auto arr = make_unique<int[]>(n);

    fillArray(arr, n);

    cout << "Массив квадратов: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}