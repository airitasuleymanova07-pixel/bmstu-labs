#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

// Структура для хранения информации о книге
struct Book {
    string title;
    string author;
    int year;
};

// Функция для ввода данных о книгах и сохранения в файл
void createAndFillFile() {
    ofstream file("books.txt", ios::app);
    if (!file.is_open()) {
        cerr << "Ошибка открытия файла books.txt" << endl;
        return;
    }

    cout << "=== СОЗДАНИЕ И ЗАПОЛНЕНИЕ ФАЙЛА ===" << endl;

    string title, author;
    int year;

    while (true) {
        cout << "Введите название книги (пустая строка для завершения): ";
        getline(cin, title);

        if (title.empty()) {
            break;
        }

        cout << "Введите автора книги: ";
        getline(cin, author);

        cout << "Введите год выпуска: ";
        cin >> year;
        cin.ignore(); // Очистка буфера после ввода числа

        // Запись в файл
        file << title << ";" << author << ";" << year << endl;
        cout << "Книга добавлена в файл!" << endl << endl;
    }

    file.close();
    cout << "Завершение ввода данных." << endl;
}

// Функция для чтения книг из файла в вектор
vector<Book> readBooksFromFile() {
    vector<Book> books;
    ifstream file("books.txt");

    if (!file.is_open()) {
        return books;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string title, author, yearStr;

        getline(ss, title, ';');
        getline(ss, author, ';');
        getline(ss, yearStr, ';');

        if (!title.empty() && !author.empty() && !yearStr.empty()) {
            Book book;
            book.title = title;
            book.author = author;
            book.year = stoi(yearStr);
            books.push_back(book);
        }
    }

    file.close();
    return books;
}

// Функция для записи книг в файл
void writeBooksToFile(const vector<Book>& books) {
    ofstream file("books.txt");

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла books.txt для записи" << endl;
        return;
    }

    for (const auto& book : books) {
        file << book.title << ";" << book.author << ";" << book.year << endl;
    }

    file.close();
}

// Функция поиска книги по названию
void searchBook() {
    vector<Book> books = readBooksFromFile();

    if (books.empty()) {
        cout << "Файл пуст или не найден!" << endl;
        return;
    }

    string searchTitle;
    cout << "Введите название книги для поиска: ";
    getline(cin, searchTitle);

    bool found = false;
    ofstream output("output.txt", ios::app);

    output << "=== РЕЗУЛЬТАТЫ ПОИСКА ===" << endl;
    cout << "=== РЕЗУЛЬТАТЫ ПОИСКА ===" << endl;

    for (const auto& book : books) {
        if (book.title.find(searchTitle) != string::npos) {
            cout << "Название: " << book.title << endl;
            cout << "Автор: " << book.author << endl;
            cout << "Год: " << book.year << endl;
            cout << "-------------------" << endl;

            output << "Название: " << book.title << endl;
            output << "Автор: " << book.author << endl;
            output << "Год: " << book.year << endl;
            output << "-------------------" << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "Книга с названием '" << searchTitle << "' не найдена." << endl;
        output << "Книга с названием '" << searchTitle << "' не найдена." << endl;
    }

    output.close();
}

// Функции сравнения для сортировки
bool compareByAuthor(const Book& a, const Book& b) {
    return a.author < b.author;
}

bool compareByYear(const Book& a, const Book& b) {
    return a.year < b.year;
}

// Функция сортировки книг
void sortBooks() {
    vector<Book> books = readBooksFromFile();

    if (books.empty()) {
        cout << "Файл пуст или не найден!" << endl;
        return;
    }

    int choice;
    cout << "Выберите критерий сортировки:" << endl;
    cout << "1 - по автору" << endl;
    cout << "2 - по году выпуска" << endl;
    cout << "Ваш выбор: ";
    cin >> choice;
    cin.ignore();

    if (choice == 1) {
        sort(books.begin(), books.end(), compareByAuthor);
        cout << "Книги отсортированы по автору." << endl;
    }
    else if (choice == 2) {
        sort(books.begin(), books.end(), compareByYear);
        cout << "Книги отсортированы по году выпуска." << endl;
    }
    else {
        cout << "Неверный выбор!" << endl;
        return;
    }

    // Запись отсортированных данных обратно в файл
    writeBooksToFile(books);

    // Запись результатов в output.txt
    ofstream output("output.txt", ios::app);
    output << "=== РЕЗУЛЬТАТЫ СОРТИРОВКИ ===" << endl;
    if (choice == 1) {
        output << "Сортировка по автору:" << endl;
    }
    else {
        output << "Сортировка по году выпуска:" << endl;
    }

    for (const auto& book : books) {
        output << "Название: " << book.title << ", Автор: " << book.author
            << ", Год: " << book.year << endl;
    }
    output << "-------------------" << endl;
    output.close();

    cout << "Результаты сортировки сохранены в файл." << endl;
}

// Функция добавления новой книги
void addBook() {
    ofstream file("books.txt", ios::app);

    if (!file.is_open()) {
        cerr << "Ошибка открытия файла books.txt" << endl;
        return;
    }

    string title, author;
    int year;

    cout << "=== ДОБАВЛЕНИЕ НОВОЙ КНИГИ ===" << endl;
    cout << "Введите название книги: ";
    getline(cin, title);

    cout << "Введите автора книги: ";
    getline(cin, author);

    cout << "Введите год выпуска: ";
    cin >> year;
    cin.ignore();

    file << title << ";" << author << ";" << year << endl;
    file.close();

    // Запись в output.txt
    ofstream output("output.txt", ios::app);
    output << "=== ДОБАВЛЕНИЕ НОВОЙ КНИГИ ===" << endl;
    output << "Название: " << title << ", Автор: " << author
        << ", Год: " << year << endl;
    output << "-------------------" << endl;
    output.close();

    cout << "Книга успешно добавлена!" << endl;
}

// Функция вывода книг по году выпуска
void displayBooksByYear() {
    vector<Book> books = readBooksFromFile();

    if (books.empty()) {
        cout << "Файл пуст или не найден!" << endl;
        return;
    }

    int maxYear;
    cout << "Введите максимальный год выпуска: ";
    cin >> maxYear;
    cin.ignore();

    ofstream output("output.txt", ios::app);
    output << "=== КНИГИ ДО " << maxYear << " ГОДА ===" << endl;
    cout << "=== КНИГИ ДО " << maxYear << " ГОДА ===" << endl;

    bool found = false;
    for (const auto& book : books) {
        if (book.year <= maxYear) {
            cout << "Название: " << book.title << endl;
            cout << "Автор: " << book.author << endl;
            cout << "Год: " << book.year << endl;
            cout << "-------------------" << endl;

            output << "Название: " << book.title << endl;
            output << "Автор: " << book.author << endl;
            output << "Год: " << book.year << endl;
            output << "-------------------" << endl;

            found = true;
        }
    }

    if (!found) {
        cout << "Книги до " << maxYear << " года не найдены." << endl;
        output << "Книги до " << maxYear << " года не найдены." << endl;
    }

    output.close();
}

// Функция для отображения всех книг
void displayAllBooks() {
    vector<Book> books = readBooksFromFile();

    if (books.empty()) {
        cout << "Файл пуст или не найден!" << endl;
        return;
    }

    cout << "=== ВСЕ КНИГИ ===" << endl;
    for (const auto& book : books) {
        cout << "Название: " << book.title << endl;
        cout << "Автор: " << book.author << endl;
        cout << "Год: " << book.year << endl;
        cout << "-------------------" << endl;
    }
}

// Главное меню
void showMenu() {
    int choice;

    do {
        cout << "\n=== МЕНЮ УПРАВЛЕНИЯ БИБЛИОТЕКОЙ ===" << endl;
        cout << "1. Создание и заполнение файла книгами" << endl;
        cout << "2. Поиск книги по названию" << endl;
        cout << "3. Сортировка книг" << endl;
        cout << "4. Добавление новой книги" << endl;
        cout << "5. Вывод книг по году выпуска" << endl;
        cout << "6. Показать все книги" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            createAndFillFile();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            sortBooks();
            break;
        case 4:
            addBook();
            break;
        case 5:
            displayBooksByYear();
            break;
        case 6:
            displayAllBooks();
            break;
        case 0:
            cout << "Программа завершена." << endl;
            break;
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
    } while (choice != 0);
}

int main() {
    // Установка русской локали для корректного отображения кириллицы
    setlocale(LC_ALL, "Russian");

    cout << "Программа для управления библиотекой книг" << endl;
    showMenu();

    return 0;
}