#include <iostream>
#include <vector>
#include <limits>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

// ������� ��� �������� ���������� ���� �����
int orientation(const Point& p, const Point& q, const Point& r) {
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0;  // �����������
    return (val > 0) ? 1 : 2; // 1 - �� �������, 2 - ������ �������
}

// ������� �������� ����������� ��������
bool doIntersect(const Point& p1, const Point& q1, const Point& p2, const Point& q2) {
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);

    // ����� ������
    if (o1 != o2 && o3 != o4)
        return true;

    // ����������� ������ (��������������)
    if (o1 == 0 && onSegment(p1, p2, q1)) return true;
    if (o2 == 0 && onSegment(p1, q2, q1)) return true;
    if (o3 == 0 && onSegment(p2, p1, q2)) return true;
    if (o4 == 0 && onSegment(p2, q1, q2)) return true;

    return false;
}

// ��������������� ������� ��� ��������, ����� �� ����� q �� ������� pr
bool onSegment(const Point& p, const Point& q, const Point& r) {
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
        q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y))
        return true;
    return false;
}

// �������� ������� �������� �������������� ����� ��������������
bool inpol(const vector<Point>& polygon, const Point& point) {
    int n = polygon.size();
    if (n < 3) return false; // ������������� ������ ����� ���� �� 3 �������

    // ������� ����� ��� ���� (������ �� ��������� ��������������)
    Point extreme = { numeric_limits<int>::max(), point.y };

    int count = 0; // ������� �����������
    int i = 0;

    do {
        int next = (i + 1) % n;

        // ��������� ����������� �������� ����� � �����
        if (doIntersect(polygon[i], polygon[next], point, extreme)) {
            // ���� ����� ����������� � ������ � ����� �� ���
            if (orientation(polygon[i], polygon[next], point) == 0) {
                return onSegment(polygon[i], point, polygon[next]);
            }
            count++;
        }
        i = next;
    } while (i != 0);

    // ���� ���������� ����������� �������� - ����� ������
    return count % 2 == 1;
}

int main() {
    setlocale(LC_ALL, "rus");

    int n;
    cout << "������� ���������� ������ ��������������: ";
    cin >> n;

    vector<Point> polygon(n);
    cout << "������� ���������� ������ �������������� (x y):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "������� " << i + 1 << ": ";
        cin >> polygon[i].x >> polygon[i].y;
    }

    Point testPoint;
    cout << "������� ���������� �������� ����� (x y): ";
    cin >> testPoint.x >> testPoint.y;

    // ��������� �������������� ����� ��������������
    if (inpol(polygon, testPoint)) {
        cout << "����� ��������� ������ ��������������" << endl;
    }
    else {
        cout << "����� ��������� ������� ��������������" << endl;
    }

    return 0;
}