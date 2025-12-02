#include <iostream>
#include <fstream>
#include <locale.h>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    int numbers[] = { 15, 23, 7, 42, 18, 91, 3, 56, 77, 10 };
    int count = sizeof(numbers) / sizeof(numbers[0]);

    ofstream outFile("numbers.bin", ios::binary);

    if (!outFile.is_open()) {
        cout << "Ошибка: не удалось создать файл numbers.bin" << endl;
        return 1;
    }

    outFile.write(reinterpret_cast<char*>(numbers), sizeof(numbers));
    outFile.close();

    cout << "Массив записан в бинарный файл numbers.bin" << endl << endl;

    ifstream inFile("numbers.bin", ios::binary);

    if (!inFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл numbers.bin" << endl;
        return 1;
    }

    inFile.seekg(0, ios::end);
    size_t fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg);

    int* buffer = new int[count];
    inFile.read(reinterpret_cast<char*>(buffer), fileSize);
    inFile.close();

    int sum = 0;
    cout << "Прочитанные числа из файла:" << endl;
    for (int i = 0; i < count; i++) {
        cout << buffer[i] << " ";
        sum += buffer[i];
    }

    cout << endl << endl;
    cout << "Размер файла: " << fileSize << " байт" << endl;
    cout << "Количество чисел: " << count << endl;
    cout << "Сумма чисел: " << sum << endl;

    delete[] buffer;

    return 0;
}