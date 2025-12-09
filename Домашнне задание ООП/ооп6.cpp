#include <iostream>
#include <string>

using namespace std;

// Класс Rectangle
class Rectangle {
private:
    double length;  // Длина прямоугольника
    double width;   // Ширина прямоугольника

public:
    // Конструктор с параметрами для инициализации атрибутов
    Rectangle(double len, double wid) {
        length = len;
        width = wid;
    }

    // Метод для вычисления площади
    double calculateArea() {
        return length * width;
    }

    // Метод для вычисления периметра
    double calculatePerimeter() {
        return 2 * (length + width);
    }

    // Метод для вывода информации о прямоугольнике
    void displayInfo() {
        cout << "Длина: " << length
            << ", Ширина: " << width
            << ", Площадь: " << calculateArea()
            << ", Периметр: " << calculatePerimeter() << endl;
    }
};

int main() {
    setlocale(LC_ALL, "rus"); // Для корректного отображения кириллицы

    // Создание объекта класса Rectangle с инициализацией атрибутов
    Rectangle myRect(5.5, 3.2);

    // Вывод информации о прямоугольнике с использованием метода displayInfo
    cout << "Информация о прямоугольнике:" << endl;
    myRect.displayInfo();

    return 0;
}