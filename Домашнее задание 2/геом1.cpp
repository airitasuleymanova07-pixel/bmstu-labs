#include <iostream>
#include <cmath>

using namespace std;
double triangle(double coord[3][2]) {
    double x1 = coord[0][0], y1 = coord[0][1];
    double x2 = coord[1][0], y2 = coord[1][1];
    double x3 = coord[2][0], y3 = coord[2][1];
    return 0.5 * abs(x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
}
int main() {
    double var[3][2];
    setlocale(LC_ALL, "rus");
    cout << "Введите координаты трех вершин треугольника:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Вершина " << (i + 1) << " - x координата: ";
        cin >> var[i][0];
        cout << "Вершина " << (i + 1) << " - y координата: ";
        cin >> var[i][1];
    }
    double s = triangle(var);
    cout << "Площадь треугольника: " << s << endl;
    return 0;
}