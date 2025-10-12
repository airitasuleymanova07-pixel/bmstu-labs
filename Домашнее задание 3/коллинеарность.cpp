#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x1, y1, x2, y2, x3, y3;
    setlocale(LC_ALL, "rus");
    cout << "Введите координаты трех точек:" << endl;
    cout << "A(x1 y1): ";
    cin >> x1 >> y1;
    cout << "B(x2 y2): ";
    cin >> x2 >> y2;
    cout << "C(x3 y3): ";
    cin >> x3 >> y3;

    double area = 0.5 * abs((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));

    double zero = 0;

    if (area == zero) {
        cout << "Точки коллинеарны" << endl;
    }
    else {
        cout << "Точки не коллинеарны" << endl;

    }

    return 0;
}