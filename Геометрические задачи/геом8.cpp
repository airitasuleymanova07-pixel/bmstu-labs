#include <iostream>
#include <cmath>
using namespace std;
int main() {
    double x1, y1, x2, y2;
    cout << "¬ведите координаты первой точки (x1 y1): ";
    cin >> x1 >> y1;
    cout << "¬ведите координаты второй точки (x2 y2): ";
    cin >> x2 >> y2;
    double dx = x2 - x1;
    double dy = y2 - y1;
    double distance = sqrt(dx * dx + dy * dy);
    cout << "ƒлина отрезка между точками: " << distance << endl;
    return 0;
}