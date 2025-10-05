#include <iostream>
#include <cmath>
using namespace std;
double distance(double x1, double y1, double x2, double y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}
int main() {
    double coord[4][2];
    cout << "������� ���������� ������� ������ ��������������:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "������� " << (i + 1) << ":" << endl;
        cout << "  x ����������: ";
        cin >> coord[i][0];
        cout << "  y ����������: ";
        cin >> coord[i][1];
    }
    double diagonal = distance(coord[0][0], coord[0][1],
        coord[2][0], coord[2][1]);
    cout << "����� ���������: " << diagonal << endl;
    return 0;
}