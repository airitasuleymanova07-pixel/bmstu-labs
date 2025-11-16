#include <iostream>
#include <memory>
#include <locale>
using namespace std;

unique_ptr<int[]> createArray(int n) {
    auto arr = make_unique<int[]>(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }
    return arr;
}

int main() {
    setlocale(LC_ALL, "rus");

    int n = 6;
    auto arr = createArray(n);

    cout << "Массив из функции: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}