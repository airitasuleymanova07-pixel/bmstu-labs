#include <iostream>
#include <queue>
#include <string>
#include <locale.h>

using namespace std;

void addEvent(queue<string>& eventQueue, const string& event) {
    eventQueue.push(event);
    cout << "Событие добавлено: " << event << endl;
}

void processEvents(queue<string>& eventQueue) {
    if (eventQueue.empty()) {
        cout << "Очередь событий пуста." << endl;
        return;
    }

    int count = 0;
    const int MAX_PROCESS = 5;

    cout << "\nОбработка событий:" << endl;
    cout << "==================" << endl;

    while (!eventQueue.empty() && count < MAX_PROCESS) {
        cout << "Обрабатывается: " << eventQueue.front() << endl;
        eventQueue.pop();
        count++;
    }

    if (count == 0) {
        cout << "Событий для обработки нет." << endl;
    }
    else {
        cout << "Обработано событий: " << count << endl;
    }
}

int main() {
    setlocale(LC_ALL, "rus");

    queue<string> eventQueue;

    int choice;
    string event;

    // Добавляем несколько начальных событий для примера
    eventQueue.push("Запрос на подключение клиента A");
    eventQueue.push("Получение данных от клиента B");
    eventQueue.push("Запрос на аутентификацию клиента C");
    eventQueue.push("Отправка ответа клиенту D");
    eventQueue.push("Логирование активности");

    do {
        cout << "\nСетевое приложение - Обработка событий" << endl;
        cout << "======================================" << endl;
        cout << "1. Добавить новое событие" << endl;
        cout << "2. Обработать события (до 5 за раз)" << endl;
        cout << "3. Показать все ожидающие события" << endl;
        cout << "4. Показать количество событий в очереди" << endl;
        cout << "5. Добавить тестовые события" << endl;
        cout << "6. Очистить очередь событий" << endl;
        cout << "7. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore(); // Очищаем буфер ввода

        switch (choice) {
        case 1:
            cout << "Введите описание события: ";
            getline(cin, event);
            addEvent(eventQueue, event);
            break;

        case 2:
            processEvents(eventQueue);
            break;

        case 3:
            if (eventQueue.empty()) {
                cout << "Очередь событий пуста." << endl;
            }
            else {
                cout << "\nОжидающие события:" << endl;
                cout << "==================" << endl;
                queue<string> tempQueue = eventQueue;
                int position = 1;
                while (!tempQueue.empty()) {
                    cout << position << ". " << tempQueue.front() << endl;
                    tempQueue.pop();
                    position++;
                }
            }
            break;

        case 4:
            cout << "Событий в очереди: " << eventQueue.size() << endl;
            break;

        case 5:
            addEvent(eventQueue, "Запрос на загрузку файла");
            addEvent(eventQueue, "Проверка авторизации");
            addEvent(eventQueue, "Обновление статистики");
            addEvent(eventQueue, "Отправка уведомления");
            addEvent(eventQueue, "Резервное копирование");
            cout << "Добавлено 5 тестовых событий." << endl;
            break;

        case 6:
            while (!eventQueue.empty()) {
                eventQueue.pop();
            }
            cout << "Очередь событий очищена." << endl;
            break;

        case 7:
            cout << "Завершение работы сетевого приложения." << endl;
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }

    } while (choice != 7);

    return 0;
}