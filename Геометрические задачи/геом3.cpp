#include <iostream>
#include <utility>  // ��� make_pair

using namespace std;
pair<double, double> triangle(double coord[3][2]) {
	int x1 = coord[0][0], y1 = coord[0][1];
	int x2 = coord[1][0], y2 = coord[1][1];
	int x3 = coord[2][0], y3 = coord[2][1];
	double smx = (x1 + x2 + x3) / 3.0;
	double smy = (y2 + y3 + y1) / 3.0;
	return make_pair(smx, smy);
}
int main() {
    double var[3][2];
    setlocale(LC_ALL, "rus");
    cout << "������� ���������� ���� ������ ������������:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "������� " << (i + 1) << " - x ����������: ";
        cin >> var[i][0];
        cout << "������� " << (i + 1) << " - y ����������: ";
        cin >> var[i][1];
    }
    auto result = triangle(var); 
    cout << "����� ���� x: " << result.first << endl;
    cout << "����� ���� y: " << result.second << endl;

    return 0;
}
    
