#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

// ������� ��� ��������� ��������������� ������ ������ �� ����
void getSortedLetters(const char* input, char* output) {
    int index = 0;

    // ��������� ������ ����� � �������� � ������� ��������
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[index++] = tolower(input[i]);
        }
    }
    output[index] = '\0';

    //��������� �����
    sort(output, output + index);
}

int main() {
    setlocale(LC_ALL, "rus");

    char str1[256], str2[256];
    char sorted1[256], sorted2[256];

    cout << "������� ������ ������: ";
    cin.getline(str1, 256);

    cout << "������� ������ ������: ";
    cin.getline(str2, 256);

    // �������� ��������������� ��������� ������������������
    getSortedLetters(str1, sorted1);
    getSortedLetters(str2, sorted2);

    cout << "��������������� ����� ������ 1: " << sorted1 << endl;
    cout << "��������������� ����� ������ 2: " << sorted2 << endl;

    // ���������� ��������������� ������������������
    if (strcmp(sorted1, sorted2) == 0) {
        cout << "��" << endl;
    }
    else {
        cout << "���" << endl;
    }

    return 0;
}