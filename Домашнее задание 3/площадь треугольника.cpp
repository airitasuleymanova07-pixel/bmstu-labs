#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x1, y1, x2, y2, x3, y3;
    setlocale(LC_ALL, "rus");

    cout << "¬ведите координаты первой точки (x1 y1): ";
    cin >> x1 >> y1;

    cout << "¬ведите координаты второй точки (x2 y2): ";
    cin >> x2 >> y2;

    cout << "¬ведите координаты третьей точки (x3 y3): ";
    cin >> x3 >> y3;

    // | x1  y1  1 |
    // | x2  y2  1 |
    // | x3  y3  1 |
    double det = x1 * (y2 * 1 - 1 * y3)
        - y1 * (x2 * 1 - 1 * x3)
        + 1 * (x2 * y3 - y2 * x3);

    double area = 0.5 * abs(det);

    cout << "ѕлощадь треугольника: " << area << endl;

    return 0;
}