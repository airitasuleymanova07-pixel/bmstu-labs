#include <iostream>
#include <cmath>
using namespace std;
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
int main() {
    double coord[4][2];
    cout << "Введите координаты четырех вершин прямоугольника:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "Вершина " << (i + 1) << ":" << endl;
        cout << "  x координата: ";
        cin >> coord[i][0];
        cout << "  y координата: ";
        cin >> coord[i][1];
    }
    double diagonal = distance(coord[0][0], coord[0][1],
        coord[2][0], coord[2][1]);
    cout << "Длина диагонали: " << diagonal << endl;
    return 0;
}