#include <iostream>
#include <cstring>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 100;
    char str[MAX_SIZE];
    char target;

    cout << "Введите строку: ";
    cin.getline(str, MAX_SIZE);

    cout << "Введите символ для поиска: ";
    cin >> target;

    int count = 0;
    char* ptr = str;

    while (*ptr != '\0') {
        if (*ptr == target) {
            count++;
        }
        ptr++;
    }

    cout << "Символ '" << target << "' встречается в строке " << count << " раз(а)" << endl;

    return 0;
}