#include <iostream>
#include <locale.h>
#include <iomanip>
#include <cmath>

using namespace std;

struct Circle {
    double radius;
};

struct Rectangle {
    double length;
    double width;
};

union Shape {
    Circle circle;
    Rectangle rectangle;
};

int main() {
    setlocale(LC_ALL, "rus");

    Shape figure;
    int choice;

    cout << fixed << setprecision(2);

    do {
        cout << "\nВыберите фигуру (1 - круг, 2 - прямоугольник, 0 - выход): ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите радиус круга: ";
            cin >> figure.circle.radius;
            if (figure.circle.radius > 0) {
                double area = M_PI * figure.circle.radius * figure.circle.radius;
                cout << "Площадь круга: " << area << endl;
            }
            else {
                cout << "Радиус должен быть положительным числом!" << endl;
            }
            break;

        case 2:
            cout << "Введите длину прямоугольника: ";
            cin >> figure.rectangle.length;
            cout << "Введите ширину прямоугольника: ";
            cin >> figure.rectangle.width;

            if (figure.rectangle.length > 0 && figure.rectangle.width > 0) {
                double area = figure.rectangle.length * figure.rectangle.width;
                cout << "Площадь прямоугольника: " << area << endl;
            }
            else {
                cout << "Длина и ширина должны быть положительными числами!" << endl;
            }
            break;

        case 0:
            cout << "Выход из программы." << endl;
            break;

        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }

    } while (choice != 0);

    return 0;
}