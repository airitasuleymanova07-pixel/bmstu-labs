#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    int n;
    cout << "Введите количество вершин многоугольника: ";
    cin >> n;
    vector<double> x(n), y(n);
    cout << "Введите координаты вершин (x y):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Вершина " << (i + 1) << ": ";
        cin >> x[i] >> y[i];
    }
    double perimeter = 0.0;
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        int side = distance(x[i], y[i], x[next], y[next]);
        perimeter += side;

        cout << "Сторона между вершинами " << (i + 1) << " и " << (next + 1)
            << ": " << side << endl;
    }

    cout << "Периметр многоугольника: " << perimeter << endl;

    return 0;
}
