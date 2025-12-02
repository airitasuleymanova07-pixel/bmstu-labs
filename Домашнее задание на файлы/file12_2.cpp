#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <locale.h>
#include <random>

using namespace std;
using namespace chrono;

int main() {
    setlocale(LC_ALL, "rus");

    const int NUM_COUNT = 100000;
    vector<int> numbers(NUM_COUNT);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    for (int i = 0; i < NUM_COUNT; i++) {
        numbers[i] = dis(gen);
    }

    auto measureTime = [](const string& operationName, auto operation) {
        auto start = high_resolution_clock::now();
        operation();
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);
        cout << operationName << ": " << duration.count() << " мс" << endl;
        return duration;
        };

    cout << "Сравнение скорости записи " << NUM_COUNT << " чисел в файл:" << endl;
    cout << "==========================================" << endl;

    auto time1 = measureTime("Запись каждого числа по отдельности", [&]() {
        ofstream file1("method1.bin", ios::binary);
        for (int num : numbers) {
            file1.write(reinterpret_cast<char*>(&num), sizeof(num));
        }
        file1.close();
        });

    auto time2 = measureTime("Запись всех чисел сразу", [&]() {
        ofstream file2("method2.bin", ios::binary);
        file2.write(reinterpret_cast<char*>(numbers.data()), numbers.size() * sizeof(int));
        file2.close();
        });

    cout << "==========================================" << endl;

    if (time1 > time2) {
        cout << "Второй метод быстрее на " << (time1 - time2).count() << " мс" << endl;
        cout << "Ускорение: " << fixed << setprecision(1)
            << (static_cast<double>(time1.count()) / time2.count()) << "x" << endl;
    }
    else {
        cout << "Первый метод быстрее на " << (time2 - time1).count() << " мс" << endl;
    }

    cout << endl << "Файлы созданы: method1.bin и method2.bin" << endl;

    return 0;
}