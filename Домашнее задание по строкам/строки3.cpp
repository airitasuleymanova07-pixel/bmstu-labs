#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char str[MAX_SIZE];

    cout << "������� ������: ";
    cin.getline(str, MAX_SIZE);

    int write_index = 0; 

    for (int read_index = 0; str[read_index] != '\0'; read_index++) {
        if (!isdigit(str[read_index])) {
            str[write_index] = str[read_index];
            write_index++;
        }
    }

    str[write_index] = '\0';

    cout << "���������: " << str << endl;

    return 0;
}