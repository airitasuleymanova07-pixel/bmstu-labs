#include <iostream>

using namespace std;
int main() {
    double points[3][2];
    cout << "Введите координаты трех точек:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Точка " << (i + 1) << " - x координата: ";
        cin >> points[i][0];
        cout << "Точка " << (i + 1) << " - y координата: ";
        cin >> points[i][1];
    }
    double x1 = points[0][0];
    double y1 = points[0][1];
    double x2 = points[1][0];
    double y2 = points[1][1];
    double x3 = points[2][0];
    double y3 = points[2][1];
    double cross_product = (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
    if (cross_product == 0) {
        cout << "Точки лежат на одной прямой" << endl;
    }
    else {
        cout << "Точки НЕ лежат на одной прямой" << endl;
    }
    return 0;
}