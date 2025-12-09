#include <iostream>
#include <string>
#include <cmath>

using namespace std;

class Rectangle {
private:
    double length;  // Длина прямоугольника
    double width;   // Ширина прямоугольника

public:
    // Конструктор по умолчанию
    Rectangle() : length(0), width(0) {}

    // Конструктор с параметрами
    Rectangle(double len, double wid) : length(len), width(wid) {
        // Проверка на положительные значения
        if (len <= 0 || wid <= 0) {
            cout << "Ошибка: длина и ширина должны быть положительными числами!" << endl;
            length = width = 0;
        }
    }

    // Метод для вычисления площади
    double calculateArea() const {
        return length * width;
    }

    // Метод для вычисления периметра
    double calculatePerimeter() const {
        return 2 * (length + width);
    }

    // Метод для проверки, является ли прямоугольник квадратом
    bool isSquare() const {
        return length == width;
    }

    // Метод для вычисления диагонали
    double calculateDiagonal() const {
        return sqrt(length * length + width * width);
    }

    // Метод для вывода информации о прямоугольнике
    void displayInfo() const {
        cout << "Длина: " << length
            << ", Ширина: " << width
            << ", Площадь: " << calculateArea()
            << ", Периметр: " << calculatePerimeter() << endl;

        // Дополнительная информация
        if (isSquare()) {
            cout << "  Это квадрат!" << endl;
        }
        cout << "  Диагональ: " << calculateDiagonal() << endl;
    }

    // Геттеры
    double getLength() const {
        return length;
    }

    double getWidth() const {
        return width;
    }

    // Сеттеры с проверкой
    void setLength(double len) {
        if (len > 0) {
            length = len;
        }
        else {
            cout << "Ошибка: длина должна быть положительным числом!" << endl;
        }
    }

    void setWidth(double wid) {
        if (wid > 0) {
            width = wid;
        }
        else {
            cout << "Ошибка: ширина должна быть положительным числом!" << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    cout << "=== Программа «Прямоугольник» ===\n" << endl;

    // Способ 1: Создание с помощью конструктора с параметрами
    cout << "Пример 1: Прямоугольник с заданными параметрами" << endl;
    Rectangle rect1(5.0, 3.0);
    rect1.displayInfo();

    cout << "\nПример 2: Квадрат" << endl;
    Rectangle square(4.0, 4.0);
    square.displayInfo();

    cout << "\n--- Пользовательский ввод ---\n" << endl;

    // Способ 2: Создание с пользовательским вводом
    double len, wid;

    cout << "Введите длину прямоугольника: ";
    cin >> len;

    cout << "Введите ширину прямоугольника: ";
    cin >> wid;

    // Создание объекта с проверкой
    Rectangle rect2(len, wid);

    cout << "\nИнформация о вашем прямоугольнике:" << endl;
    rect2.displayInfo();

    cout << "\n--- Работа с методами отдельно ---\n" << endl;

    // Использование отдельных методов
    cout << "Площадь: " << rect2.calculateArea() << endl;
    cout << "Периметр: " << rect2.calculatePerimeter() << endl;

    if (rect2.isSquare()) {
        cout << "Это квадрат!" << endl;
    }
    else {
        cout << "Это не квадрат (длина и ширина разные)." << endl;
    }

    cout << "Диагональ: " << rect2.calculateDiagonal() << endl;

    cout << "\n--- Изменение параметров прямоугольника ---\n" << endl;

    // Демонстрация работы сеттеров
    cout << "Увеличим длину на 2 единицы и ширину на 1 единицу..." << endl;
    rect2.setLength(rect2.getLength() + 2);
    rect2.setWidth(rect2.getWidth() + 1);

    cout << "После изменений:" << endl;
    rect2.displayInfo();

    cout << "\n--- Несколько прямоугольников ---\n" << endl;

    // Создание массива прямоугольников
    Rectangle rectangles[3] = {
        Rectangle(6, 4),
        Rectangle(3.5, 2.5),
        Rectangle(7, 7)  // квадрат
    };

    cout << "Несколько прямоугольников:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << "Прямоугольник " << (i + 1) << ": ";
        rectangles[i].displayInfo();
    }

    // Пример с некорректными данными
    cout << "\n--- Проверка на некорректные данные ---\n" << endl;
    Rectangle badRect(-5, 3);  // Отрицательная длина

    return 0;
}