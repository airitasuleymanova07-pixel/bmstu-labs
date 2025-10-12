#include <iostream>
using namespace std;
// �������� � �������� 
void transpose(int n, int matrix[][100], int result[][100]) { //��������� ������������ ������� ���������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[j][i];
        }
    }
}

void antiTranspose(int n, int matrix[][100], int result[][100]) { //��������� ������������ �������� ���������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[n - 1 - j][n - 1 - i];
        }
    }
}

void verticalReflection(int n, int matrix[][100], int result[][100]) { //����������� ��������� ������������ ������������ ���
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[i][n - 1 - j];
        }
    }
}

void horizontalReflection(int n, int matrix[][100], int result[][100]) {  //����������� ��������� ������������ �������������� ���
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = matrix[n - 1 - i][j];
        }
    }
}

bool areMatricesEqual(int n, int mat1[][100], int mat2[][100]) { // ��������� ���� ������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (mat1[i][j] != mat2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void printMatrix(int n, int matrix[][100]) { //����� ������
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j];
            if (j < n - 1) cout << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    setlocale(LC_ALL, "rus");
    // ���� ������� �������
    cout << "������� ������ ������� N: ";
    cin >> n;

    // �������� 
    if (n < 1 || n > 100) {
        cout << "������: ������ ������� ������ ���� �� 1 �� 100" << endl;
        return 1;
    }

    // ����������, ���� ������
    int matrix[100][100];
    int matrix1[100][100], matrix2[100][100], matrix3[100][100], matrix4[100][100];

    // ���� ���������
    cout << "������� �������� ������� " << n << "x" << n << ":" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << "������� [" << i << "][" << j << "]: ";
            cin >> matrix[i][j];
        }
    }

    transpose(n, matrix, matrix1);
    antiTranspose(n, matrix, matrix2);
    verticalReflection(n, matrix, matrix3);
    horizontalReflection(n, matrix, matrix4);

    cout << "�������� �������:" << endl;
    printMatrix(n, matrix);

    cout << "������� 1 (��������� ������������ ������� ���������):" << endl;
    printMatrix(n, matrix1);

    cout << "������� 2 (��������� ������������ �������� ���������):" << endl;
    printMatrix(n, matrix2);

    cout << "������� 3 (���������� ��������� ������������ ������������ ���):" << endl;
    printMatrix(n, matrix3);

    cout << "������� 4 (���������� ��������� ������������ �������������� ���):" << endl;
    printMatrix(n, matrix4);

    // ��������� 
    int matrices[4][100][100];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrices[0][i][j] = matrix1[i][j];
            matrices[1][i][j] = matrix2[i][j];
            matrices[2][i][j] = matrix3[i][j];
            matrices[3][i][j] = matrix4[i][j];
        }
    }

    // ����� ����������� ���
    bool foundMatches = false;
    cout << "����������� �������:" << endl;

    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (areMatricesEqual(n, matrices[i], matrices[j])) {
                cout << "������� " << i + 1 << " � ������� " << j + 1 << " ���������" << endl;
                foundMatches = true;
            }
        }
    }

    if (!foundMatches) {
        cout << "NONE" << endl;
    }

    return 0;
}