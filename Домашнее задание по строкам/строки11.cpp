#include <iostream>
#include <cstring>

using namespace std;

bool allUnique(const char* str, int start, int k) {
    for (int i = start; i < start + k - 1; i++) {
        for (int j = i + 1; j < start + k; j++) {
            if (str[i] == str[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char str[MAX_SIZE];
    int k;

    cout << "введите строку: ";
    cin.getline(str, MAX_SIZE);

    cout << "введите k: ";
    cin >> k;

    int len = strlen(str);

    if (k > len) {
        cout << "k больше длины строки" << endl;
        return 0;
    }

    cout << "подстроки длины " << k << " с уникальными символами:" << endl;
    bool found = false;

    for (int i = 0; i <= len - k; i++) {
        if (allUnique(str, i, k)) {
            found = true;
            for (int j = i; j < i + k; j++) {
                cout << str[j];
            }
            cout << endl;
        }
    }

    if (!found) {
        cout << "таких подстрок нет" << endl;
    }

    return 0;
}