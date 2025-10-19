#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char text[MAX_SIZE];
    int shift;

    cout << "������� �����: ";
    cin.getline(text, MAX_SIZE);

    cout << "������� �����: ";
    cin >> shift;

    for (int i = 0; text[i] != '\0'; i++) {
        if (isupper(text[i])) {
            text[i] = (text[i] - 'A' + shift) % 26 + 'A';
            if (text[i] < 'A') {
                text[i] += 26;
            }
        }
        else if (islower(text[i])) {
            text[i] = (text[i] - 'a' + shift) % 26 + 'a';
            if (text[i] < 'a') {
                text[i] += 26;
            }
        }
    }

    cout << "���������: " << text << endl;

    return 0;
}