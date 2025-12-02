#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <locale.h>
#include <iomanip>

using namespace std;

struct Student {
    int id;
    char name[50];
    int age;
    double average_grade;
};

int main() {
    setlocale(LC_ALL, "rus");

    Student students[] = {
        {1, "Иван Петров", 20, 4.5},
        {2, "Мария Сидорова", 19, 4.8},
        {3, "Алексей Иванов", 21, 4.2}
    };

    int studentCount = sizeof(students) / sizeof(Student);

    ofstream outFile("students.dat", ios::binary);

    if (!outFile.is_open()) {
        cout << "Ошибка: не удалось создать файл students.dat" << endl;
        return 1;
    }

    for (int i = 0; i < studentCount; i++) {
        outFile.write(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }

    outFile.close();

    cout << "Студенты записаны в бинарный файл students.dat" << endl << endl;

    ifstream inFile("students.dat", ios::binary);

    if (!inFile.is_open()) {
        cout << "Ошибка: не удалось открыть файл students.dat" << endl;
        return 1;
    }

    cout << "Список всех студентов:" << endl;
    cout << "======================" << endl;

    Student student;
    int totalStudents = 0;
    Student bestStudent;
    double highestGrade = 0;

    inFile.seekg(0, ios::end);
    streampos fileSize = inFile.tellg();
    inFile.seekg(0, ios::beg);

    totalStudents = fileSize / sizeof(Student);

    cout << fixed << setprecision(1);

    for (int i = 0; i < totalStudents; i++) {
        inFile.read(reinterpret_cast<char*>(&student), sizeof(Student));

        cout << "ID: " << student.id << endl;
        cout << "Имя: " << student.name << endl;
        cout << "Возраст: " << student.age << endl;
        cout << "Средний балл: " << student.average_grade << endl;
        cout << "----------------------" << endl;

        if (student.average_grade > highestGrade) {
            highestGrade = student.average_grade;
            bestStudent = student;
        }
    }

    inFile.close();

    cout << endl << "Статистика:" << endl;
    cout << "Всего студентов: " << totalStudents << endl;
    cout << "Лучший студент: " << bestStudent.name
        << " (средний балл: " << bestStudent.average_grade << ")" << endl;

    return 0;
}