#include <iostream>
using namespace std;

int main() {
    // x + y + z = 6
    // 2x - y + 3z = 14  
    // -x + 4y - z = 2

    double a1 = 1, b1 = 1, c1 = 1, d1 = 6;
    double a2 = 2, b2 = -1, c2 = 3, d2 = 14;
    double a3 = -1, b3 = 4, c3 = -1, d3 = 2;

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
        cout << x << " + " << y << " + " << z << " = " << x + y + z << endl;
        cout << "2*" << x << " - " << y << " + 3*" << z << " = " << 2 * x - y + 3 * z << endl;
        cout << "-" << x << " + 4*" << y << " - " << z << " = " << -x + 4 * y - z << endl;
    }
    else {
        cout << "Система не имеет единственного решения" << endl;
    }

    return 0;
}