#include <iostream>
#include <cstring>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char A[MAX_SIZE], B[MAX_SIZE];

    cout << "введите строку A: ";
    cin.getline(A, MAX_SIZE);

    cout << "введите строку B: ";
    cin.getline(B, MAX_SIZE);

    bool all_found = true;

    for (int i = 0; B[i] != '\0'; i++) {
        bool found = false;

        for (int j = 0; A[j] != '\0'; j++) {
            if (B[i] == A[j]) {
                found = true;
                break;
            }
        }

        if (!found) {
            all_found = false;
            cout << "символ '" << B[i] << "' не найден в строке A" << endl;
            break;
        }
    }

    if (all_found) {
        cout << "да, все символы из B содержатся в A" << endl;
    }
    else {
        cout << "нет, не все символы из B содержатся в A" << endl;
    }

    return 0;
}