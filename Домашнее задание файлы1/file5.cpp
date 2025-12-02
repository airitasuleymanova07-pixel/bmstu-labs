#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    // Открываем файл для чтения
    ifstream inputFile("input.txt");

    // Проверяем, успешно ли открылся файл
    if (!inputFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл input.txt" << endl;
        cout << "Убедитесь, что файл существует в текущей папке." << endl;
        return 1;
    }

    char ch;
    int charCount = 0;

    // Считываем файл посимвольно с помощью метода .get(ch)
    while (inputFile.get(ch)) {
        charCount++;  // Увеличиваем счетчик для каждого символа
    }

    // Закрываем файл
    inputFile.close();

    // Выводим результат
    cout << "Количество символов в файле: " << charCount << endl;

    return 0;
}