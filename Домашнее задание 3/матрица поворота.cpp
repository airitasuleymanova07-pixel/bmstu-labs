#include <iostream>
#include <cmath>
using namespace std;

int main() {
    const double PI = 3.14159265358979323846;

    double x, y, angle;
    setlocale(LC_ALL, "rus");
    cout << "Введите координаты точки (x y): ";
    cin >> x >> y;

    cout << "Введите угол поворота в градусах: ";
    cin >> angle;

    double theta = angle * PI / 180.0;

    double cos_theta = cos(theta);
    double sin_theta = sin(theta);

    double x_new = cos_theta * x + sin_theta * y;
    double y_new = -sin_theta * x + cos_theta * y;

    cout << "Новые координаты точки после поворота на " << angle << "°:" << endl;
    cout << "x' = " << x_new << endl;
    cout << "y' = " << y_new << endl;

    return 0;
}