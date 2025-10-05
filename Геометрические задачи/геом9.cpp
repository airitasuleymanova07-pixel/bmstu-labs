#include <iostream>
using namespace std;
struct Point {
    double x, y;
};
// Проверка пересечения двух отрезков
bool segmentsIntersect(Point p1, Point q1, Point p2, Point q2) {
    // Вычисляем векторные произведения
    double cross1 = (q1.x - p1.x) * (p2.y - p1.y) - (q1.y - p1.y) * (p2.x - p1.x);
    double cross2 = (q1.x - p1.x) * (q2.y - p1.y) - (q1.y - p1.y) * (q2.x - p1.x);
    double cross3 = (q2.x - p2.x) * (p1.y - p2.y) - (q2.y - p2.y) * (p1.x - p2.x);
    double cross4 = (q2.x - p2.x) * (q1.y - p2.y) - (q2.y - p2.y) * (q1.x - p2.x);

    // Основное условие пересечения
    return (cross1 * cross2 < 0) && (cross3 * cross4 < 0);
}
// Проверка пересечения двух многоугольников
bool checkpol(Point poly1[], int size1, Point poly2[], int size2) {
    for (int i = 0; i < size1; i++) {
        Point p1 = poly1[i];
        Point q1 = poly1[(i + 1) % size1];

        for (int j = 0; j < size2; j++) {
            Point p2 = poly2[j];
            Point q2 = poly2[(j + 1) % size2];

            if (segmentsIntersect(p1, q1, p2, q2)) {
                return true;
            }
        }
    }
    return false;
}
int main() {
    int size1, size2;
    setlocale(LC_ALL, "rus");
    cout << "Введите количество вершин первого многоугольника: ";
    cin >> size1;
    Point* poly1 = new Point[size1]; // Динамический массив для первого многоугольника
    cout << "Введите координаты вершин первого многоугольника:" << endl;
    for (int i = 0; i < size1; i++) {
        cout << "Вершина " << (i + 1) << " (x y): ";
        cin >> poly1[i].x >> poly1[i].y;
    }
    // Ввод второго многоугольника
    cout << "Введите количество вершин второго многоугольника: ";
    cin >> size2;
    Point* poly2 = new Point[size2]; // Динамический массив для второго многоугольника
    cout << "Введите координаты вершин второго многоугольника:" << endl;
    for (int i = 0; i < size2; i++) {
        cout << "Вершина " << (i + 1) << " (x y): ";
        cin >> poly2[i].x >> poly2[i].y;
    }
    // Проверка пересечения
    if (checkpol(poly1, size1, poly2, size2)) {
        cout << "Многоугольники ПЕРЕСЕКАЮТСЯ" << endl;
    }
    else {
        cout << "Многоугольники НЕ пересекаются" << endl;
    }
    delete[] poly1;
    delete[] poly2;
    return 0;
}