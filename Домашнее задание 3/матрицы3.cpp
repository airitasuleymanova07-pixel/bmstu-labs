#include <iostream>
using namespace std;

int main() {
    int n, m;
    setlocale(LC_ALL, "rus");

    cout << "������� ������ ������� (N M): ";
    cin >> n >> m;

    int matrix[100][100];

    cout << "������� �������� ������� " << n << "x" << m << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cout << "������� [" << i + 1 << "][" << j + 1 << "]: ";
            cin >> matrix[i][j];
        }
    }

    int rowMin[100], rowMax[100];
    int colMin[100], colMax[100];

    for (int i = 0; i < n; i++) {
        rowMin[i] = matrix[i][0];
        rowMax[i] = matrix[i][0];
        for (int j = 1; j < m; j++) {
            if (matrix[i][j] < rowMin[i]) {
                rowMin[i] = matrix[i][j];
            }
            if (matrix[i][j] > rowMax[i]) {
                rowMax[i] = matrix[i][j];
            }
        }
    }

    for (int j = 0; j < m; j++) {
        colMin[j] = matrix[0][j];
        colMax[j] = matrix[0][j];
        for (int i = 1; i < n; i++) {
            if (matrix[i][j] < colMin[j]) {
                colMin[j] = matrix[i][j];
            }
            if (matrix[i][j] > colMax[j]) {
                colMax[j] = matrix[i][j];
            }
        }
    }

    // ����� �������� �����
    bool found = false;

    cout << "���������� ������ �������� �����:" << endl;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // ��� A
            if (matrix[i][j] == rowMin[i] && matrix[i][j] == colMax[j]) {
                cout << "A " << matrix[i][j] << " " << i + 1 << " " << j + 1 << endl;
                found = true;
            }
            // ��� B
            if (matrix[i][j] == rowMax[i] && matrix[i][j] == colMin[j]) {
                cout << "B " << matrix[i][j] << " " << i + 1 << " " << j + 1 << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "NONE" << endl;
    }

    return 0;
}