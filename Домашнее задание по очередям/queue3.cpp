#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <locale.h>

using namespace std;

struct Product {
    string name;
    int quantity;
    double price;
};

struct Order {
    int orderId;
    string customerName;
    string customerEmail;
    vector<Product> products;
    double totalAmount;
    string status;

    Order(int id, string name, string email) :
        orderId(id), customerName(name), customerEmail(email),
        totalAmount(0), status("В обработке") {
    }

    void addProduct(string productName, int qty, double price) {
        Product p = { productName, qty, price };
        products.push_back(p);
        totalAmount += qty * price;
    }

    void displayOrder() const {
        cout << "\n=== Заказ #" << orderId << " ===" << endl;
        cout << "Клиент: " << customerName << endl;
        cout << "Email: " << customerEmail << endl;
        cout << "Статус: " << status << endl;
        cout << "Товары:" << endl;
        cout << "--------------------------------" << endl;

        for (size_t i = 0; i < products.size(); i++) {
            cout << i + 1 << ". " << products[i].name
                << " x" << products[i].quantity
                << " - " << products[i].price * products[i].quantity << " руб." << endl;
        }

        cout << "--------------------------------" << endl;
        cout << "Итого: " << totalAmount << " руб." << endl;
    }
};

void addOrder(queue<Order>& orderQueue, const Order& newOrder) {
    orderQueue.push(newOrder);
    cout << "Заказ #" << newOrder.orderId << " добавлен в очередь обработки." << endl;
}

void processOrder(queue<Order>& orderQueue) {
    if (orderQueue.empty()) {
        cout << "Очередь заказов пуста." << endl;
        return;
    }

    Order currentOrder = orderQueue.front();
    cout << "\n=== Обработка заказа ===" << endl;
    currentOrder.displayOrder();

    cout << "\nЗаказ #" << currentOrder.orderId << " обработан и отправлен клиенту "
        << currentOrder.customerName << endl;

    orderQueue.pop();
}

int main() {
    setlocale(LC_ALL, "rus");

    queue<Order> orderQueue;
    int nextOrderId = 1;

    int choice;

    do {
        cout << "\nИнтернет-магазин - Система обработки заказов" << endl;
        cout << "=============================================" << endl;
        cout << "1. Создать новый заказ" << endl;
        cout << "2. Обработать следующий заказ" << endl;
        cout << "3. Показать все ожидающие заказы" << endl;
        cout << "4. Показать количество заказов в очереди" << endl;
        cout << "5. Добавить тестовые заказы" << endl;
        cout << "6. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            string name, email;
            cout << "Введите имя клиента: ";
            getline(cin, name);
            cout << "Введите email клиента: ";
            getline(cin, email);

            Order newOrder(nextOrderId++, name, email);

            int productCount;
            cout << "Сколько товаров в заказе? ";
            cin >> productCount;

            for (int i = 0; i < productCount; i++) {
                string productName;
                int quantity;
                double price;

                cin.ignore();
                cout << "\nТовар " << i + 1 << ":" << endl;
                cout << "Название: ";
                getline(cin, productName);
                cout << "Количество: ";
                cin >> quantity;
                cout << "Цена за единицу: ";
                cin >> price;

                newOrder.addProduct(productName, quantity, price);
            }

            addOrder(orderQueue, newOrder);
            break;
        }

        case 2:
            processOrder(orderQueue);
            break;

        case 3:
            if (orderQueue.empty()) {
                cout << "Очередь заказов пуста." << endl;
            }
            else {
                cout << "\nОжидающие заказы:" << endl;
                cout << "==================" << endl;
                queue<Order> tempQueue = orderQueue;
                int position = 1;

                while (!tempQueue.empty()) {
                    Order order = tempQueue.front();
                    cout << "\n" << position << ". Заказ #" << order.orderId
                        << " - " << order.customerName
                        << " (" << order.totalAmount << " руб.)";
                    tempQueue.pop();
                    position++;
                }
                cout << endl;
            }
            break;

        case 4:
            cout << "Заказов в очереди: " << orderQueue.size() << endl;
            break;

        case 5: {
            // Тестовые заказы
            Order order1(nextOrderId++, "Иван Петров", "ivan@mail.ru");
            order1.addProduct("Ноутбук Dell", 1, 75000);
            order1.addProduct("Мышка беспроводная", 1, 2500);
            addOrder(orderQueue, order1);

            Order order2(nextOrderId++, "Мария Сидорова", "maria@mail.ru");
            order2.addProduct("Книга 'C++ для начинающих'", 2, 1500);
            order2.addProduct("Блокнот", 3, 350);
            addOrder(orderQueue, order2);

            Order order3(nextOrderId++, "Алексей Иванов", "alex@mail.ru");
            order3.addProduct("Смартфон Samsung", 1, 45000);
            order3.addProduct("Чехол для телефона", 1, 1200);
            order3.addProduct("Карта памяти 128GB", 1, 2500);
            addOrder(orderQueue, order3);

            cout << "Добавлено 3 тестовых заказа." << endl;
            break;
        }

        case 6:
            cout << "Завершение работы системы обработки заказов." << endl;
            break;

        default:
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }

    } while (choice != 6);

    return 0;
}