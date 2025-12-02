#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <locale.h>

using namespace std;

struct Book {
    string title;
    string author;
    int year;
    string genre;
};

struct Library {
    vector<Book> books;
    int count;

    Library() : count(0) {}

    void addBook(const Book& book) {
        books.push_back(book);
        count++;
        cout << "Книга добавлена в библиотеку." << endl;
    }

    void removeBook(const string& title) {
        auto it = find_if(books.begin(), books.end(),
            [&title](const Book& b) { return b.title == title; });

        if (it != books.end()) {
            books.erase(it);
            count--;
            cout << "Книга удалена из библиотеки." << endl;
        }
        else {
            cout << "Книга с таким названием не найдена." << endl;
        }
    }

    void searchByAuthor(const string& author) {
        cout << "\n=== Книги автора " << author << " ===" << endl;
        bool found = false;

        for (const auto& book : books) {
            if (book.author == author) {
                cout << "Название: " << book.title << endl;
                cout << "Автор: " << book.author << endl;
                cout << "Год издания: " << book.year << endl;
                cout << "Жанр: " << book.genre << endl;
                cout << "------------------------" << endl;
                found = true;
            }
        }

        if (!found) {
            cout << "Книги этого автора не найдены." << endl;
        }
    }

    void displayAllBooks() {
        if (books.empty()) {
            cout << "Библиотека пуста." << endl;
            return;
        }

        cout << "\n=== Все книги в библиотеке ===" << endl;
        for (size_t i = 0; i < books.size(); i++) {
            cout << "Книга " << i + 1 << ":" << endl;
            cout << "  Название: " << books[i].title << endl;
            cout << "  Автор: " << books[i].author << endl;
            cout << "  Год издания: " << books[i].year << endl;
            cout << "  Жанр: " << books[i].genre << endl;
            cout << "------------------------" << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");

    Library library;
    int choice;

    do {
        cout << "\n=== Библиотечная система ===" << endl;
        cout << "1. Добавить новую книгу" << endl;
        cout << "2. Удалить книгу по названию" << endl;
        cout << "3. Найти книги по автору" << endl;
        cout << "4. Показать все книги" << endl;
        cout << "5. Показать количество книг" << endl;
        cout << "6. Выйти" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            Book newBook;
            cout << "Введите название книги: ";
            getline(cin, newBook.title);
            cout << "Введите автора книги: ";
            getline(cin, newBook.author);
            cout << "Введите год издания: ";
            cin >> newBook.year;
            cin.ignore();
            cout << "Введите жанр книги: ";
            getline(cin, newBook.genre);
            library.addBook(newBook);
            break;
        }

        case 2: {
            string title;
            cout << "Введите название книги для удаления: ";
            getline(cin, title);
            library.removeBook(title);
            break;
        }

        case 3: {
            string author;
            cout << "Введите автора для поиска: ";
            getline(cin, author);
            library.searchByAuthor(author);
            break;
        }

        case 4:
            library.displayAllBooks();
            break;

        case 5:
            cout << "Количество книг в библиотеке: " << library.count << endl;
            break;

        case 6:
            cout << "Программа завершена." << endl;
            break;

        default:
            cout << "Неверный выбор!" << endl;
        }

    } while (choice != 6);

    return 0;
}