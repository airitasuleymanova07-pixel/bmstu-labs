#include <iostream>
using namespace std;

int main() {
    int num;
    setlocale(LC_ALL, "rus");
    cout << "Введите целое число: ";
    cin >> num;
    if (num % 3 == 0 && num % 5 == 0) {
        cout << "Число делится на 3 и 5 одновременно." << endl;
    }
    else if (num % 3 == 0) {
        cout << "Число делится только на 3." << endl;
    }
    else if (num % 5 == 0) {
        cout << "Число делится только на 5." << endl;
    }
    else {
        cout << "Число не делится ни на 3, ни на 5." << endl;
    }
    return 0;
}