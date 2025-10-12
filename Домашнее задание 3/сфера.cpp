#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
    double x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
    setlocale(LC_ALL, "rus");
    cout << "Введите координаты четырех точек:" << endl;
    cout << "A(x1 y1 z1): ";
    cin >> x1 >> y1 >> z1;
    cout << "B(x2 y2 z2): ";
    cin >> x2 >> y2 >> z2;
    cout << "C(x3 y3 z3): ";
    cin >> x3 >> y3 >> z3;
    cout << "D(x4 y4 z4): ";
    cin >> x4 >> y4 >> z4;

    // Уравнение сферы: x² + y² + z² + Ax + By + Cz + D = 0
    // Для каждой точки получаем уравнение:
    // x_i^2 + y_i^2 + z_i^2 + A*x_i + B*y_i + C*z_i + D = 0

    double mat[4][4] = {
        {x1, y1, z1, 1},
        {x2, y2, z2, 1},
        {x3, y3, z3, 1},
        {x4, y4, z4, 1}
    };

    // Вектор правых частей:
    double rhs[4] = {
        -(x1 * x1 + y1 * y1 + z1 * z1),
        -(x2 * x2 + y2 * y2 + z2 * z2),
        -(x3 * x3 + y3 * y3 + z3 * z3),
        -(x4 * x4 + y4 * y4 + z4 * z4)
    };

    // Вычисляем определитель основной матрицы
    double det = mat[0][0] * (mat[1][1] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2])
        - mat[1][2] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1])
        + mat[1][3] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1]))
        - mat[0][1] * (mat[1][0] * (mat[2][2] * mat[3][3] - mat[2][3] * mat[3][2])
            - mat[1][2] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0])
            + mat[1][3] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0]))
        + mat[0][2] * (mat[1][0] * (mat[2][1] * mat[3][3] - mat[2][3] * mat[3][1])
            - mat[1][1] * (mat[2][0] * mat[3][3] - mat[2][3] * mat[3][0])
            + mat[1][3] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]))
        - mat[0][3] * (mat[1][0] * (mat[2][1] * mat[3][2] - mat[2][2] * mat[3][1])
            - mat[1][1] * (mat[2][0] * mat[3][2] - mat[2][2] * mat[3][0])
            + mat[1][2] * (mat[2][0] * mat[3][1] - mat[2][1] * mat[3][0]));

    if (abs(det) == 0) {
        cout << "Точки лежат в одной плоскости или совпадают, сфера не определена" << endl;
        return 0;
    }

    // Вычисляем определители для A, B, C, D
    double detA, detB, detC, detD;

    // Для A
    double matA[4][4] = {
        {rhs[0], y1, z1, 1},
        {rhs[1], y2, z2, 1},
        {rhs[2], y3, z3, 1},
        {rhs[3], y4, z4, 1}
    };
    detA = matA[0][0] * (matA[1][1] * (matA[2][2] * matA[3][3] - matA[2][3] * matA[3][2])
        - matA[1][2] * (matA[2][1] * matA[3][3] - matA[2][3] * matA[3][1])
        + matA[1][3] * (matA[2][1] * matA[3][2] - matA[2][2] * matA[3][1]))
        - matA[0][1] * (matA[1][0] * (matA[2][2] * matA[3][3] - matA[2][3] * matA[3][2])
            - matA[1][2] * (matA[2][0] * matA[3][3] - matA[2][3] * matA[3][0])
            + matA[1][3] * (matA[2][0] * matA[3][2] - matA[2][2] * matA[3][0]))
        + matA[0][2] * (matA[1][0] * (matA[2][1] * matA[3][3] - matA[2][3] * matA[3][1])
            - matA[1][1] * (matA[2][0] * matA[3][3] - matA[2][3] * matA[3][0])
            + matA[1][3] * (matA[2][0] * matA[3][1] - matA[2][1] * matA[3][0]))
        - matA[0][3] * (matA[1][0] * (matA[2][1] * matA[3][2] - matA[2][2] * matA[3][1])
            - matA[1][1] * (matA[2][0] * matA[3][2] - matA[2][2] * matA[3][0])
            + matA[1][2] * (matA[2][0] * matA[3][1] - matA[2][1] * matA[3][0]));

    // Для B
    double matB[4][4] = {
        {x1, rhs[0], z1, 1},
        {x2, rhs[1], z2, 1},
        {x3, rhs[2], z3, 1},
        {x4, rhs[3], z4, 1}
    };
    detB = matB[0][0] * (matB[1][1] * (matB[2][2] * matB[3][3] - matB[2][3] * matB[3][2])
        - matB[1][2] * (matB[2][1] * matB[3][3] - matB[2][3] * matB[3][1])
        + matB[1][3] * (matB[2][1] * matB[3][2] - matB[2][2] * matB[3][1]))
        - matB[0][1] * (matB[1][0] * (matB[2][2] * matB[3][3] - matB[2][3] * matB[3][2])
            - matB[1][2] * (matB[2][0] * matB[3][3] - matB[2][3] * matB[3][0])
            + matB[1][3] * (matB[2][0] * matB[3][2] - matB[2][2] * matB[3][0]))
        + matB[0][2] * (matB[1][0] * (matB[2][1] * matB[3][3] - matB[2][3] * matB[3][1])
            - matB[1][1] * (matB[2][0] * matB[3][3] - matB[2][3] * matB[3][0])
            + matB[1][3] * (matB[2][0] * matB[3][1] - matB[2][1] * matB[3][0]))
        - matB[0][3] * (matB[1][0] * (matB[2][1] * matB[3][2] - matB[2][2] * matB[3][1])
            - matB[1][1] * (matB[2][0] * matB[3][2] - matB[2][2] * matB[3][0])
            + matB[1][2] * (matB[2][0] * matB[3][1] - matB[2][1] * matB[3][0]));

    // Для C
    double matC[4][4] = {
        {x1, y1, rhs[0], 1},
        {x2, y2, rhs[1], 1},
        {x3, y3, rhs[2], 1},
        {x4, y4, rhs[3], 1}
    };
    detC = matC[0][0] * (matC[1][1] * (matC[2][2] * matC[3][3] - matC[2][3] * matC[3][2])
        - matC[1][2] * (matC[2][1] * matC[3][3] - matC[2][3] * matC[3][1])
        + matC[1][3] * (matC[2][1] * matC[3][2] - matC[2][2] * matC[3][1]))
        - matC[0][1] * (matC[1][0] * (matC[2][2] * matC[3][3] - matC[2][3] * matC[3][2])
            - matC[1][2] * (matC[2][0] * matC[3][3] - matC[2][3] * matC[3][0])
            + matC[1][3] * (matC[2][0] * matC[3][2] - matC[2][2] * matC[3][0]))
        + matC[0][2] * (matC[1][0] * (matC[2][1] * matC[3][3] - matC[2][3] * matC[3][1])
            - matC[1][1] * (matC[2][0] * matC[3][3] - matC[2][3] * matC[3][0])
            + matC[1][3] * (matC[2][0] * matC[3][1] - matC[2][1] * matC[3][0]))
        - matC[0][3] * (matC[1][0] * (matC[2][1] * matC[3][2] - matC[2][2] * matC[3][1])
            - matC[1][1] * (matC[2][0] * matC[3][2] - matC[2][2] * matC[3][0])
            + matC[1][2] * (matC[2][0] * matC[3][1] - matC[2][1] * matC[3][0]));

    // Для D
    double matD[4][4] = {
        {x1, y1, z1, rhs[0]},
        {x2, y2, z2, rhs[1]},
        {x3, y3, z3, rhs[2]},
        {x4, y4, z4, rhs[3]}
    };
    detD = matD[0][0] * (matD[1][1] * (matD[2][2] * matD[3][3] - matD[2][3] * matD[3][2])
        - matD[1][2] * (matD[2][1] * matD[3][3] - matD[2][3] * matD[3][1])
        + matD[1][3] * (matD[2][1] * matD[3][2] - matD[2][2] * matD[3][1]))
        - matD[0][1] * (matD[1][0] * (matD[2][2] * matD[3][3] - matD[2][3] * matD[3][2])
            - matD[1][2] * (matD[2][0] * matD[3][3] - matD[2][3] * matD[3][0])
            + matD[1][3] * (matD[2][0] * matD[3][2] - matD[2][2] * matD[3][0]))
        + matD[0][2] * (matD[1][0] * (matD[2][1] * matD[3][3] - matD[2][3] * matD[3][1])
            - matD[1][1] * (matD[2][0] * matD[3][3] - matD[2][3] * matD[3][0])
            + matD[1][3] * (matD[2][0] * matD[3][1] - matD[2][1] * matD[3][0]))
        - matD[0][3] * (matD[1][0] * (matD[2][1] * matD[3][2] - matD[2][2] * matD[3][1])
            - matD[1][1] * (matD[2][0] * matD[3][2] - matD[2][2] * matD[3][0])
            + matD[1][2] * (matD[2][0] * matD[3][1] - matD[2][1] * matD[3][0]));

    // коэффициенты
    double A = detA / det;
    double B = detB / det;
    double C = detC / det;
    double D = detD / det;

    //центр и радиус сферы
    double x0 = -A / 2;
    double y0 = -B / 2;
    double z0 = -C / 2;
    double r = sqrt(x0 * x0 + y0 * y0 + z0 * z0 - D);
    cout << fixed << setprecision(2);

    cout << "Уравнение сферы:" << endl;
    cout << "x^2 + y^2 + z^2 + " << A << "x + " << B << "y + " << C << "z + " << D << " = 0" << endl;

    cout << "Центр сферы: (" << x0 << ", " << y0 << ", " << z0 << ")" << endl;
    cout << "Радиус сферы: " << r << endl;

    cout << "Уравнение в каноническом виде:" << endl;
    cout << "(x - " << x0 << ")^2 + (y - " << y0 << ")^2 + (z - " << z0 << ")^2 = " << r * r << endl;

    return 0;
}