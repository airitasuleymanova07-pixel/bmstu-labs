#include <iostream>
using namespace std;

int main() {
    int n, m;
    setlocale(LC_ALL, "rus");
    cout << "������� ������ �������:";
    cin >> n >> m;

    int matrix[100][100];

    cout << "������� �������� �������:";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> matrix[i][j];
        }
    }

    // ������� 
    int top = 0, bottom = n - 1, left = 0, right = m - 1;

    while (top <= bottom && left <= right) {
        // ������ �� ������� ������
        for (int j = left; j <= right; j++) {
            cout << matrix[top][j] << " ";
        }
        top++;

        // ���� �� ������� �������
        for (int i = top; i <= bottom; i++) {
            cout << matrix[i][right] << " ";
        }
        right--;

        // ��������, ���� �� ��� ������ ��� ������ ����� �������
        if (top <= bottom) {
            // ����� �� ������ ������
            for (int j = right; j >= left; j--) {
                cout << matrix[bottom][j] << " ";
            }
            bottom--;
        }

        // ��������, ���� �� ��� ������� ��� ������ ����� �����
        if (left <= right) {
            // ����� �� ������ �������
            for (int i = bottom; i >= top; i--) {
                cout << matrix[i][left] << " ";
            }
            left++;
        }
    }

    return 0;
}