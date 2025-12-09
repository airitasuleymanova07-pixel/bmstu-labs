#include <iostream>
#include <string>

using namespace std;

// Базовый класс Shape
class Shape {
protected:
    double length; // Длина фигуры

public:
    // Конструктор с параметром
    Shape(double length) : length(length) {}

    // Виртуальный метод для получения информации (для возможного переопределения)
    virtual void displayInfo() const {
        cout << "Длина: " << length;
    }

    // Виртуальный деструктор (для корректного удаления объектов производных классов)
    virtual ~Shape() {}

    // Геттер для длины
    double getLength() const {
        return length;
    }
};

// Производный класс Rectangle
class Rectangle : public Shape {
private:
    double width; // Ширина прямоугольника

public:
    // Конструктор с параметрами
    Rectangle(double length, double width) : Shape(length), width(width) {}

    // Метод для вычисления площади
    double calculateArea() const {
        return length * width;
    }

    // Метод для вычисления периметра
    double calculatePerimeter() const {
        return 2 * (length + width);
    }

    // Переопределенный метод для вывода информации
    void displayInfo() const override {
        cout << "Длина: " << length
            << ", Ширина: " << width
            << ", Площадь: " << calculateArea()
            << ", Периметр: " << calculatePerimeter() << endl;
    }

    // Геттер для ширины
    double getWidth() const {
        return width;
    }
};

int main() {
    setlocale(LC_ALL, "rus"); // Установка русской локали

    // Пример 1: Создание объекта с заданными значениями
    cout << "Пример 1: Прямоугольник с заданными параметрами" << endl;
    Rectangle rect1(5.5, 3.2);
    rect1.displayInfo();

    cout << "\n--- Пример с пользовательским вводом ---\n" << endl;

    // Пример 2: Создание объекта с пользовательским вводом
    double length, width;

    cout << "Введите длину прямоугольника: ";
    cin >> length;

    cout << "Введите ширину прямоугольника: ";
    cin >> width;

    // Проверка на корректность ввода
    if (length <= 0 || width <= 0) {
        cout << "Ошибка: длина и ширина должны быть положительными числами!" << endl;
        return 1;
    }

    // Создание объекта Rectangle
    Rectangle rect2(length, width);

    cout << "\nИнформация о прямоугольнике:" << endl;
    rect2.displayInfo();

    // Дополнительный пример использования отдельных методов
    cout << "\nДополнительные вычисления:" << endl;
    cout << "Площадь: " << rect2.calculateArea() << endl;
    cout << "Периметр: " << rect2.calculatePerimeter() << endl;

    // Демонстрация полиморфизма
    cout << "\n--- Демонстрация полиморфизма ---\n" << endl;

    Shape* shapePtr = &rect2; // Указатель базового класса на объект производного класса
    cout << "Использование указателя базового класса:" << endl;

    // Вызов переопределенного метода через указатель базового класса
    shapePtr->displayInfo();

    return 0;
}