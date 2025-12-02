#include <iostream>
#include <locale.h>
#include <iomanip>

using namespace std;

struct DateComponents {
    int year;
    int month;
    int day;
};

struct TimeComponents {
    int hour;
    int minute;
    int second;
};

union DateTime {
    struct {
        DateComponents date;
        TimeComponents time;
    } components;

    struct {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
    } all;
};

bool isValidDate(int year, int month, int day) {
    if (year < 1 || month < 1 || month > 12 || day < 1) return false;

    int daysInMonth;
    switch (month) {
    case 2:
        daysInMonth = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? 29 : 28;
        break;
    case 4: case 6: case 9: case 11:
        daysInMonth = 30;
        break;
    default:
        daysInMonth = 31;
    }

    return day <= daysInMonth;
}

bool isValidTime(int hour, int minute, int second) {
    return hour >= 0 && hour <= 23 &&
        minute >= 0 && minute <= 59 &&
        second >= 0 && second <= 59;
}

int main() {
    setlocale(LC_ALL, "rus");

    DateTime dt;

    cout << "Введите год: ";
    cin >> dt.all.year;

    cout << "Введите месяц (1-12): ";
    cin >> dt.all.month;

    cout << "Введите день: ";
    cin >> dt.all.day;

    if (!isValidDate(dt.all.year, dt.all.month, dt.all.day)) {
        cout << "Неверная дата!" << endl;
        return 1;
    }

    cout << "Введите час (0-23): ";
    cin >> dt.all.hour;

    cout << "Введите минуту (0-59): ";
    cin >> dt.all.minute;

    cout << "Введите секунду (0-59): ";
    cin >> dt.all.second;

    if (!isValidTime(dt.all.hour, dt.all.minute, dt.all.second)) {
        cout << "Неверное время!" << endl;
        return 1;
    }

    cout << "\nДата и время: ";
    cout << dt.all.year << "-"
        << dt.all.month << "-"
        << dt.all.day << " "
        << setw(2) << setfill('0') << dt.all.hour << ":"
        << setw(2) << setfill('0') << dt.all.minute << ":"
        << setw(2) << setfill('0') << dt.all.second << endl;

    cout << "\nКомпоненты даты и времени:" << endl;
    cout << "Год: " << dt.components.date.year << endl;
    cout << "Месяц: " << dt.components.date.month << endl;
    cout << "День: " << dt.components.date.day << endl;
    cout << "Час: " << dt.components.time.hour << endl;
    cout << "Минута: " << dt.components.time.minute << endl;
    cout << "Секунда: " << dt.components.time.second << endl;

    return 0;
}