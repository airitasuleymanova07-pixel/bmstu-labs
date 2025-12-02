#include <iostream>
#include <string>
#include <vector>
#include <locale.h>

using namespace std;

struct Employee {
    string name;
    int age;
    string position;
    double salary;
};

int main() {
    setlocale(LC_ALL, "rus");

    int n;
    cout << "Введите количество сотрудников: ";
    cin >> n;

    if (n <= 0) {
        cout << "Количество сотрудников должно быть положительным!" << endl;
        return 1;
    }

    vector<Employee> employees(n);

    for (int i = 0; i < n; i++) {
        cout << "\nВведите данные сотрудника " << i + 1 << ":" << endl;

        cout << "Введите имя сотрудника: ";
        cin.ignore();
        getline(cin, employees[i].name);

        cout << "Введите возраст сотрудника: ";
        cin >> employees[i].age;

        cout << "Введите должность сотрудника: ";
        cin.ignore();
        getline(cin, employees[i].position);

        cout << "Введите зарплату сотрудника: ";
        cin >> employees[i].salary;
    }

    Employee youngest = employees[0];
    Employee oldest = employees[0];
    double totalSalary = 0;

    for (const auto& emp : employees) {
        if (emp.age < youngest.age) {
            youngest = emp;
        }
        if (emp.age > oldest.age) {
            oldest = emp;
        }
        totalSalary += emp.salary;
    }

    double averageSalary = totalSalary / n;

    cout << "\n=== Результаты ===" << endl;
    cout << "Самый молодой сотрудник: " << youngest.name
        << ", возраст: " << youngest.age
        << ", должность: " << youngest.position
        << ", зарплата: " << youngest.salary << endl;

    cout << "Самый старший сотрудник: " << oldest.name
        << ", возраст: " << oldest.age
        << ", должность: " << oldest.position
        << ", зарплата: " << oldest.salary << endl;

    cout << "Средняя зарплата всех сотрудников: " << averageSalary << endl;

    return 0;
}