#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    ifstream numbersFile("numbers.txt");

    if (!numbersFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл numbers.txt" << endl;
        return 1;
    }

    int number;
    int count = 0;
    int sum = 0;

    while (numbersFile >> number) {
        count++;
        sum += number;
    }

    numbersFile.close();

    cout << "Количество чисел: " << count << endl;
    cout << "Сумма: " << sum << endl;

    if (count > 0) {
        double average = static_cast<double>(sum) / count;
        cout << "Среднее: " << average << endl;
    }
    else {
        cout << "Среднее: 0" << endl;
    }

    return 0;
}