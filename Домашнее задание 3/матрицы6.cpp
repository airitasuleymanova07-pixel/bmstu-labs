#include <iostream>
using namespace std;

int main() {
    // 2x + 3y = 13
    // 5x - y = 9

    double a1 = 2, b1 = 3, c1 = 13;
    double a2 = 5, b2 = -1, c2 = 9;

    double det = a1 * b2 - a2 * b1;
    double det_x = c1 * b2 - c2 * b1;
    double det_y = a1 * c2 - a2 * c1;

    if (det != 0) {
        double x = det_x / det;
        double y = det_y / det;
        setlocale(LC_ALL, "rus");
        cout << "Решение системы:" << endl;
        cout << "2x + 3y = 13" << endl;
        cout << "5x - y = 9" << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;

        cout << "Проверка:" << endl;
        cout << "2*" << x << " + 3*" << y << " = " << 2 * x + 3 * y << endl;
        cout << "5*" << x << " - " << y << " = " << 5 * x - y << endl;
    }
    else {
        cout << "Система не имеет единственного решения" << endl;
    }

    return 0;
}