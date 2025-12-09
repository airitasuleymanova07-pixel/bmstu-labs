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
    // Конструктор с параметрами
    Book(const string& bookTitle, const string& bookAuthor, int bookYear)
        : title(bookTitle), author(bookAuthor), year(bookYear) {
    }

    // Метод для вывода информации о книге
    void displayInfo() const {
        cout << "Название: " << title
            << ", Автор: " << author
            << ", Год выпуска: " << year << endl;
    }

    // Геттеры (для доступа к приватным полям, если понадобится)
    string getTitle() const {
        return title;
    }

    string getAuthor() const {
        return author;
    }

    int getYear() const {
        return year;
    }

    // Сеттеры (для изменения значений полей, если понадобится)
    void setTitle(const string& newTitle) {
        title = newTitle;
    }

    void setAuthor(const string& newAuthor) {
        author = newAuthor;
    }

    void setYear(int newYear) {
        year = newYear;
    }
};

int main() {
    setlocale(LC_ALL, "rus"); // Установка русской локали

    cout << "=== Программа «Книга» ===\n" << endl;

    // Способ 1: Создание объекта с прямым указанием значений в конструкторе
    cout << "Способ 1: Создание с заданными параметрами" << endl;
    Book book1("Преступление и наказание", "Фёдор Достоевский", 1866);
    book1.displayInfo();

    cout << "\n--- Способ 2: Создание с пользовательским вводом ---\n" << endl;

    // Способ 2: Создание объекта с пользовательским вводом
    string title, author;
    int year;

    cout << "Введите название книги: ";
    getline(cin, title);

    cout << "Введите автора книги: ";
    getline(cin, author);

    cout << "Введите год выпуска: ";
    cin >> year;
    cin.ignore(); // Очистка буфера после ввода числа

    // Создание объекта с введенными значениями
    Book book2(title, author, year);

    cout << "\nИнформация о вашей книге:" << endl;
    book2.displayInfo();

    // Дополнительный пример: изменение данных книги
    cout << "\n--- Изменение данных книги ---\n" << endl;
    book2.setYear(year + 1); // Допустим, переиздание через год
    cout << "После переиздания:" << endl;
    book2.displayInfo();

    // Пример использования геттеров
    cout << "\n--- Использование геттеров ---\n" << endl;
    cout << "Название (через геттер): " << book1.getTitle() << endl;
    cout << "Автор (через геттер): " << book1.getAuthor() << endl;
    cout << "Год (через геттер): " << book1.getYear() << endl;

    // Создание нескольких книг
    cout << "\n--- Библиотека книг ---\n" << endl;
    Book library[] = {
        Book("Война и мир", "Лев Толстой", 1869),
        Book("Мастер и Маргарита", "Михаил Булгаков", 1966),
        Book("Евгений Онегин", "Александр Пушкин", 1833)
    };

    cout << "Книги в библиотеке:" << endl;
    for (int i = 0; i < 3; i++) {
        cout << i + 1 << ". ";
        library[i].displayInfo();
    }

    return 0;
}