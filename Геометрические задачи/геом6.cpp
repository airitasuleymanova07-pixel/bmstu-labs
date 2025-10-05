#include <iostream>
using namespace std;
double coord(double x1, double y1, double x2, double y2, double x3, double y3) {
    return (x2 - x1) * (y3 - y1) - (y2 - y1) * (x3 - x1);
}
bool segm(double seg1[2][2], double seg2[2][2]) {
    double x1 = seg1[0][0], y1 = seg1[0][1];
    double x2 = seg1[1][0], y2 = seg1[1][1];
    double x3 = seg2[0][0], y3 = seg2[0][1];
    double x4 = seg2[1][0], y4 = seg2[1][1];
    double cp1 = coord(x1, y1, x2, y2, x3, y3);
    double cp2 = coord(x1, y1, x2, y2, x4, y4);
    double cp3 = coord(x3, y3, x4, y4, x1, y1);
    double cp4 = coord(x3, y3, x4, y4, x2, y2);
    return (cp1 * cp2 < 0) && (cp3 * cp4 < 0);
}
int main() {
    double segment1[2][2], segment2[2][2];
    cout << "Введите координаты первого отрезка:" << endl;
    cout << "Точка A (x y): "; cin >> segment1[0][0] >> segment1[0][1];
    cout << "Точка B (x y): "; cin >> segment1[1][0] >> segment1[1][1];
    cout << "Введите координаты второго отрезка:" << endl;
    cout << "Точка C (x y): "; cin >> segment2[0][0] >> segment2[0][1];
    cout << "Точка D (x y): "; cin >> segment2[1][0] >> segment2[1][1];
    if (segm(segment1, segment2)) {
        cout << "Отрезки пересекаются" << endl;
    }
    else {
        cout << "Отрезки НЕ пересекаются" << endl;
    }
    return 0;
}