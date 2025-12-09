#include <iostream>
#include <string>

using namespace std;

// Класс Book
class Book {
private:
    string title;   // Название книги
    string author;  // Автор книги
    int year;       // Год выпуска

public:
    // Конструктор с параметрами для инициализации атрибутов
    Book(string t, string a, int y) {
        title = t;
        author = a;
        year = y;
    }

    // Метод для вывода информации о книге
    void displayInfo() {
        cout << "Название: " << title
            << ", Автор: " << author
            << ", Год выпуска: " << year << endl;
    }
};

int main() {
    setlocale(LC_ALL, "rus"); // Для корректного отображения кириллицы

    // Создание объекта класса Book с инициализацией атрибутов
    Book myBook("Мастер и Маргарита", "Михаил Булгаков", 1966);

    // Вывод информации о книге с использованием метода displayInfo
    cout << "Информация о книге:" << endl;
    myBook.displayInfo();

    return 0;
}