#include <iostream>
using namespace std;

int main() {
    // 3x - y + 2z = 5
    // 2x + 4y - z = 6  
    // x - 3y + z = 4

    double a1 = 3, b1 = -1, c1 = 2, d1 = 5;
    double a2 = 2, b2 = 4, c2 = -1, d2 = 6;
    double a3 = 1, b3 = -3, c3 = 1, d3 = 4;

    double det = a1 * (b2 * c3 - b3 * c2) - b1 * (a2 * c3 - a3 * c2) + c1 * (a2 * b3 - a3 * b2);

    double det_x = d1 * (b2 * c3 - b3 * c2) - b1 * (d2 * c3 - d3 * c2) + c1 * (d2 * b3 - d3 * b2);

    double det_y = a1 * (d2 * c3 - d3 * c2) - d1 * (a2 * c3 - a3 * c2) + c1 * (a2 * d3 - a3 * d2);

    double det_z = a1 * (b2 * d3 - b3 * d2) - b1 * (a2 * d3 - a3 * d2) + d1 * (a2 * b3 - a3 * b2);

    if (det != 0) {
        double x = det_x / det;
        double y = det_y / det;
        double z = det_z / det;
        setlocale(LC_ALL, "rus");
        cout << "Решение системы:" << endl;
        cout << "x = " << x << endl;
        cout << "y = " << y << endl;
        cout << "z = " << z << endl;

        cout << "Проверка:" << endl;
        cout << "3*" << x << " - " << y << " + 2*" << z << " = " << 3 * x - y + 2 * z << " (5)" << endl;
        cout << "2*" << x << " + 4*" << y << " - " << z << " = " << 2 * x + 4 * y - z << " (6)" << endl;
        cout << x << " - 3*" << y << " + " << z << " = " << x - 3 * y + z << " (4)" << endl;
    }
    else {
        cout << "Система не имеет единственного решения" << endl;
    }

    return 0;
}