#include <iostream>
#include <queue>
#include <string>
#include <locale.h>

using namespace std;

void addToQueue(queue<string>& queue, const string& person) {
    queue.push(person);
    cout << person << " добавлен(а) в очередь." << endl;
}

void processQueue(queue<string>& queue) {
    if (!queue.empty()) {
        cout << "Обработан(а): " << queue.front() << endl;
        queue.pop();
    }
    else {
        cout << "Очередь пуста." << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    queue<string> supermarketQueue;

    int choice;
    string name;

    do {
        cout << "\nМеню:" << endl;
        cout << "1. Добавить человека в очередь" << endl;
        cout << "2. Обработать человека из очереди" << endl;
        cout << "3. Показать очередь" << endl;
        cout << "4. Показать размер очереди" << endl;
        cout << "5. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Введите имя человека: ";
            cin.ignore();
            getline(cin, name);
            addToQueue(supermarketQueue, name);
            break;

        case 2:
            processQueue(supermarketQueue);
            break;

        case 3:
            if (supermarketQueue.empty()) {
                cout << "Очередь пуста." << endl;
            }
            else {
                cout << "Текущая очередь:" << endl;
                queue<string> tempQueue = supermarketQueue;
                int position = 1;
                while (!tempQueue.empty()) {
                    cout << position << ". " << tempQueue.front() << endl;
                    tempQueue.pop();
                    position++;
                }
            }
            break;

        case 4:
            cout << "Людей в очереди: " << supermarketQueue.size() << endl;
            break;

        case 5:
            cout << "Выход из программы." << endl;
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    } while (choice != 5);

    return 0;
}