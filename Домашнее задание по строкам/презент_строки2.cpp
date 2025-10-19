#include <iostream>
#include <cstring>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char text[MAX_SIZE];
    char symbol;

    cout << "������� ������: ";
    cin.getline(text, MAX_SIZE);

    cout << "������� ������ ��� ��������: ";
    cin >> symbol;

    int len = strlen(text);
    int write_index = 0;

    for (int read_index = 0; read_index < len; read_index++) {
        if (text[read_index] != symbol) {
            text[write_index] = text[read_index];
            write_index++;
        }
    }

    text[write_index] = '\0';

    cout << "���������: " << text << endl;

    return 0;
}