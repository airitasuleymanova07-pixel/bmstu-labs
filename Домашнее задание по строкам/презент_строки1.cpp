#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char text[MAX_SIZE];

    cout << "������� ������: ";
    cin.getline(text, MAX_SIZE);

    int len = strlen(text);
    int max_length = 0;      // ����� ������ �������� �����
    int max_start = 0;       // ������ ������ �������� �����
    int max_end = 0;         // ����� ������ �������� �����

    int current_start = 0;   // ������ �������� �����
    int current_length = 0;  // ����� �������� �����

    for (int i = 0; i <= len; i++) {
        // ���� ������� ������ - �����, ����������� ����� �������� �����
        if (i < len && isalpha(text[i])) {
            if (current_length == 0) {
                current_start = i; // ������ ������ �����
            }
            current_length++;
        }
        else {
            // ����� �����, ���������, �� ����� �� ��� �������
            if (current_length > max_length) {
                max_length = current_length;
                max_start = current_start;
                max_end = i - 1;
            }
            current_length = 0; // ���������� ��� ���������� �����
        }
    }

    if (max_length > 0) {
        cout << "����� ������� �����: \"";
        for (int i = max_start; i <= max_end; i++) {
            cout << text[i];
        }
        cout << "\" (�����: " << max_length << " ��������)" << endl;
    }
    else {
        cout << "� ������ ��� ����" << endl;
    }

    return 0;
}