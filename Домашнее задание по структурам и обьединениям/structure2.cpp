#include <iostream>
#include <string>
#include <vector>
#include <locale.h>

using namespace std;

struct BankAccount {
    string accountNumber;
    string ownerName;
    double balance;
};

int findAccount(const vector<BankAccount>& accounts, const string& accountNumber) {
    for (size_t i = 0; i < accounts.size(); i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

int main() {
    setlocale(LC_ALL, "rus");

    vector<BankAccount> accounts;
    int choice;

    do {
        cout << "\n=== Банковская система ===" << endl;
        cout << "1. Создать новый банковский счет" << endl;
        cout << "2. Пополнить счет" << endl;
        cout << "3. Снять деньги со счета" << endl;
        cout << "4. Показать информацию о счете" << endl;
        cout << "5. Показать все счета" << endl;
        cout << "6. Выйти" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1: {
            BankAccount newAccount;
            cout << "Введите номер счета: ";
            getline(cin, newAccount.accountNumber);
            cout << "Введите имя владельца счета: ";
            getline(cin, newAccount.ownerName);
            newAccount.balance = 0;
            accounts.push_back(newAccount);
            cout << "Банковский счет создан." << endl;
            break;
        }

        case 2: {
            string accNum;
            double amount;
            cout << "Введите номер счета для пополнения: ";
            getline(cin, accNum);
            int index = findAccount(accounts, accNum);
            if (index != -1) {
                cout << "Введите сумму для пополнения: ";
                cin >> amount;
                if (amount > 0) {
                    accounts[index].balance += amount;
                    cout << "Счет пополнен на " << amount << " рублей." << endl;
                }
                else {
                    cout << "Сумма должна быть положительной!" << endl;
                }
            }
            else {
                cout << "Счет не найден!" << endl;
            }
            break;
        }

        case 3: {
            string accNum;
            double amount;
            cout << "Введите номер счета для снятия: ";
            getline(cin, accNum);
            int index = findAccount(accounts, accNum);
            if (index != -1) {
                cout << "Введите сумму для снятия: ";
                cin >> amount;
                if (amount > 0) {
                    if (accounts[index].balance >= amount) {
                        accounts[index].balance -= amount;
                        cout << "Со счета снято " << amount << " рублей." << endl;
                    }
                    else {
                        cout << "Недостаточно средств на счете!" << endl;
                    }
                }
                else {
                    cout << "Сумма должна быть положительной!" << endl;
                }
            }
            else {
                cout << "Счет не найден!" << endl;
            }
            break;
        }

        case 4: {
            string accNum;
            cout << "Введите номер счета для показа информации: ";
            getline(cin, accNum);
            int index = findAccount(accounts, accNum);
            if (index != -1) {
                cout << "\n=== Информация о счете ===" << endl;
                cout << "Номер счета: " << accounts[index].accountNumber << endl;
                cout << "Имя владельца счета: " << accounts[index].ownerName << endl;
                cout << "Баланс: " << accounts[index].balance << " рублей" << endl;
            }
            else {
                cout << "Счет не найден!" << endl;
            }
            break;
        }

        case 5: {
            if (accounts.empty()) {
                cout << "Нет созданных счетов." << endl;
            }
            else {
                cout << "\n=== Все счета ===" << endl;
                for (const auto& account : accounts) {
                    cout << "Номер: " << account.accountNumber
                        << ", Владелец: " << account.ownerName
                        << ", Баланс: " << account.balance << " руб." << endl;
                }
            }
            break;
        }

        case 6:
            cout << "Программа завершена." << endl;
            break;

        default:
            cout << "Неверный выбор!" << endl;
        }

    } while (choice != 6);

    return 0;
}