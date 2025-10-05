#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

double distance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
    int n;
    cout << "������� ���������� ������ ��������������: ";
    cin >> n;
    vector<double> x(n), y(n);
    cout << "������� ���������� ������ (x y):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "������� " << (i + 1) << ": ";
        cin >> x[i] >> y[i];
    }
    double perimeter = 0.0;
    for (int i = 0; i < n; i++) {
        int next = (i + 1) % n;
        int side = distance(x[i], y[i], x[next], y[next]);
        perimeter += side;

        cout << "������� ����� ��������� " << (i + 1) << " � " << (next + 1)
            << ": " << side << endl;
    }

    cout << "�������� ��������������: " << perimeter << endl;

    return 0;
}
