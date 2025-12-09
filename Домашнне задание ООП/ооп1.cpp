#include <iostream>
#include <string>

using namespace std;

// Базовый класс Publication
class Publication {
protected:
    string title; // Название публикации

public:
    // Конструктор с параметром
    Publication(const string& title) : title(title) {}

    // Метод для получения названия
    string getTitle() const {
        return title;
    }
};

// Производный класс Book
class Book : public Publication {
private:
    string author; // Автор книги
    int year;      // Год выпуска

public:
    // Конструктор с параметрами
    Book(const string& title, const string& author, int year)
        : Publication(title), author(author), year(year) {
    }

    // Метод для вывода информации о книге
    void displayInfo() const {
        cout << "Название: " << title
            << ", Автор: " << author
            << ", Год выпуска: " << year << endl;
    }

    // Геттеры (опционально)
    string getAuthor() const {
        return author;
    }

    int getYear() const {
        return year;
    }
};

int main() {
    setlocale(LC_ALL, "rus"); 

    // Создание объекта класса Book
    Book myBook("1984", "Джордж Оруэлл", 1949);

    // Вывод информации о книге
    cout << "Информация о книге:" << endl;
    myBook.displayInfo();

    cout << "\n--- Пример с пользовательским вводом ---\n" << endl;

    // Пример с пользовательским вводом
    string title, author;
    int year;

    cout << "Введите название книги: ";
    getline(cin, title);

    cout << "Введите автора книги: ";
    getline(cin, author);

    cout << "Введите год выпуска: ";
    cin >> year;
    cin.ignore(); // Очистка буфера после ввода числа

    // Создание второго объекта
    Book userBook(title, author, year);

    cout << "\nИнформация о вашей книге:" << endl;
    userBook.displayInfo();

    return 0;
}