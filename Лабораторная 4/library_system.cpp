#include <iostream>
#include <string>
#include <memory>
#include <pqxx/pqxx>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace pqxx;

// ================== Класс Database ==================
class Database {
private:
    unique_ptr<connection> conn;
    
    void log(const string& msg) {
        ofstream file("log.txt", ios::app);
        if (file) file << msg << endl;
    }
    
public:
    Database(const string& connStr) : conn(make_unique<connection>(connStr)) {
        if (!conn->is_open()) throw runtime_error("Connection failed");
    }
    
    // Добавление автора
    int addAuthor(const string& name, int birthYear) {
        try {
            work txn(*conn);
            string sql = "INSERT INTO authors (name, birth_year) VALUES (" + 
                         txn.quote(name) + ", " + to_string(birthYear) + ") RETURNING id";
            result res = txn.exec(sql);
            txn.commit();
            log("✓ Author added: " + name);
            return res[0][0].as<int>();
        } catch (const exception& e) {
            log("✗ Error adding author: " + string(e.what()));
            cerr << "Error: " << e.what() << endl;
            return 0;
        }
    }
    
    // Добавление книги
    int addBook(const string& title, int authorId, int year, const string& genre) {
        try {
            work txn(*conn);
            string sql = "INSERT INTO books (title, author_id, publication_year, genre) VALUES (" + 
                         txn.quote(title) + ", " + to_string(authorId) + ", " + 
                         to_string(year) + ", " + txn.quote(genre) + ") RETURNING id";
            result res = txn.exec(sql);
            txn.commit();
            log("✓ Book added: " + title);
            return res[0][0].as<int>();
        } catch (const exception& e) {
            log("✗ Error adding book: " + string(e.what()));
            cerr << "Error: " << e.what() << endl;
            return 0;
        }
    }
    
    // Добавление пользователя
    int addUser(const string& name) {
        try {
            work txn(*conn);
            string sql = "INSERT INTO users (name) VALUES (" + txn.quote(name) + ") RETURNING id";
            result res = txn.exec(sql);
            txn.commit();
            log("✓ User added: " + name);
            return res[0][0].as<int>();
        } catch (const exception& e) {
            log("✗ Error adding user: " + string(e.what()));
            cerr << "Error: " << e.what() << endl;
            return 0;
        }
    }
    
    // Взятие книги
    void borrowBook(int userId, int bookId) {
        try {
            work txn(*conn);
            string sql = "INSERT INTO borrowed_books (user_id, book_id) VALUES (" + 
                         to_string(userId) + ", " + to_string(bookId) + ")";
            txn.exec(sql);
            txn.commit();
            log("✓ Book borrowed: user=" + to_string(userId) + ", book=" + to_string(bookId));
        } catch (const exception& e) {
            log("✗ Error borrowing book: " + string(e.what()));
            cerr << "Error: " << e.what() << endl;
        }
    }
    
    // Книги автора
    void getBooksByAuthor(int authorId) {
        try {
            work txn(*conn);
            result res = txn.exec("SELECT title FROM books WHERE author_id = " + to_string(authorId));
            cout << "Author's books:" << endl;
            for (auto row : res) cout << "  - " << row["title"].c_str() << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    
    // Пользователи за год
    void getUsersLastYear() {
        try {
            work txn(*conn);
            result res = txn.exec("SELECT COUNT(*) FROM users WHERE registration_date >= CURRENT_DATE - INTERVAL '1 year'");
            cout << "Users last year:" << endl;
            cout << "Count: " << res[0][0].c_str() << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    
    // Книги за 30 дней
    void getBooksLast30Days() {
        try {
            work txn(*conn);
            result res = txn.exec("SELECT b.title FROM borrowed_books bb JOIN books b ON bb.book_id = b.id WHERE borrow_date >= CURRENT_DATE - INTERVAL '30 days'");
            cout << "Books last 30 days:" << endl;
            for (auto row : res) cout << "  - " << row["title"].c_str() << endl;
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
    
    // Топ-3 книги
    void getTop3Books() {
        try {
            work txn(*conn);
            result res = txn.exec("SELECT b.title, COUNT(*) AS cnt FROM borrowed_books bb JOIN books b ON bb.book_id = b.id GROUP BY b.title ORDER BY cnt DESC LIMIT 3");
            cout << "Top 3 popular books:" << endl;
            int i = 1;
            for (auto row : res) {
                cout << i++ << ". " << row["title"].c_str() << " (" << row["cnt"].c_str() << " borrows)" << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
};

// ================== Шаблонный класс Pair ==================
template <typename T1, typename T2>
class Pair {
public:
    T1 first;
    T2 second;
    Pair(T1 f, T2 s) : first(f), second(s) {}
};

// ================== Наследование для книг ==================
class BookBase {
protected:
    string title;
    int authorId;
    int year;
    string genre;
public:
    BookBase(string t, int aId, int y, string g) : title(t), authorId(aId), year(y), genre(g) {}
    virtual ~BookBase() = default;
};

class FictionBook : public BookBase {
public:
    FictionBook(string t, int aId, int y, string g) : BookBase(t, aId, y, g) {}
};

class NonFictionBook : public BookBase {
public:
    NonFictionBook(string t, int aId, int y, string g) : BookBase(t, aId, y, g) {}
};

// ================== Главная функция ==================
int main() {
    try {
        // Подключение к БД 
        Database db("dbname=library user=postgres password=Airita300907 host=localhost port=5432 client_encoding=UTF8");
        cout << "=== Система управления библиотекой ===\n";
        
        int choice;
        do {
            cout << "\nМеню:\n";
            cout << "1. Добавить автора\n";
            cout << "2. Добавить книгу\n";
            cout << "3. Добавить пользователя\n";
            cout << "4. Взять книгу\n";
            cout << "5. Книги автора\n";
            cout << "6. Пользователи за год\n";
            cout << "7. Книги за 30 дней\n";
            cout << "8. Топ-3 книги\n";
            cout << "0. Выход\n";
            cout << "Выбор: ";
            cin >> choice;
            cin.ignore();
            
            if (choice == 1) {
                string name;
                int year;
                cout << "Имя автора: ";
                getline(cin, name);
                cout << "Год рождения: ";
                cin >> year;
                int id = db.addAuthor(name, year);
                cout << "Автор добавлен с ID: " << id << endl;
            }
            else if (choice == 2) {
                string title, genre;
                int authorId, year;
                cout << "Название: ";
                getline(cin, title);
                cout << "ID автора: ";
                cin >> authorId;
                cout << "Год издания: ";
                cin >> year;
                cin.ignore();
                cout << "Жанр: ";
                getline(cin, genre);
                
                // Создание объектов через наследование
                BookBase* book;
                if (genre == "Фантастика" || genre == "Роман" || genre == "Приключения")
                    book = new FictionBook(title, authorId, year, genre);
                else
                    book = new NonFictionBook(title, authorId, year, genre);
                    
                int id = db.addBook(title, authorId, year, genre);
                cout << "Книга добавлена с ID: " << id << endl;
                delete book;
            }
            else if (choice == 3) {
                string name;
                cout << "Имя пользователя: ";
                getline(cin, name);
                int id = db.addUser(name);
                cout << "Пользователь добавлен с ID: " << id << endl;
            }
            else if (choice == 4) {
                int userId, bookId;
                cout << "ID пользователя: ";
                cin >> userId;
                cout << "ID книги: ";
                cin >> bookId;
                db.borrowBook(userId, bookId);
                cout << "Книга выдана" << endl;
            }
            else if (choice == 5) {
                int authorId;
                cout << "ID автора: ";
                cin >> authorId;
                cout << "Книги автора:" << endl;
                db.getBooksByAuthor(authorId);
            }
            else if (choice == 6) {
                cout << "Пользователи за последний год:" << endl;
                db.getUsersLastYear();
            }
            else if (choice == 7) {
                cout << "Книги за последние 30 дней:" << endl;
                db.getBooksLast30Days();
            }
            else if (choice == 8) {
                cout << "Топ-3 популярных книги:" << endl;
                db.getTop3Books();
            }
        } while (choice != 0);
        
        cout << "Выход..." << endl;
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}