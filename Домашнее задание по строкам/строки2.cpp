#include <iostream>
#include <cstring>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char str[MAX_SIZE];

    cout << "введите строку: ";
    cin.getline(str, MAX_SIZE);

    int length = strlen(str);
    int unique_count = 0;

    cout << "уникальные символы: ";

    for (int i = 0; i < length; i++) {
        bool is_unique = true;

        for (int j = 0; j < i; j++) {
            if (str[i] == str[j]) {
                is_unique = false;
                break;
            }
        }

        if (is_unique) {
            unique_count++;
            cout << str[i];
            if (i < length - 1) {
                bool has_more_unique = false;
                for (int k = i + 1; k < length; k++) {
                    bool is_k_unique = true;
                    for (int m = 0; m < k; m++) {
                        if (str[k] == str[m]) {
                            is_k_unique = false;
                            break;
                        }
                    }
                    if (is_k_unique) {
                        has_more_unique = true;
                        break;
                    }
                }
                if (has_more_unique) {
                    cout << ", ";
                }
            }
        }
    }

    cout << endl << "количество уникальных символов: " << unique_count << endl;

    return 0;
}