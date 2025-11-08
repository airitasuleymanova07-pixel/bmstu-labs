#include <iostream>
#include <cstring>
#include <clocale>

using namespace std;

bool isPalindrome(const char* str) {
    if (str == nullptr || *str == '\0') {
        return true;
    }

    const char* start = str;  
    const char* end = str;   

    while (*end != '\0') {
        end++;
    }
    end--;  

    while (start < end) {
        if (*start != *end) {
            return false;  
        }
        start++;
        end--;
    }

    return true;  
}

int main() {
    const int max_size = 100;
    char string[max_size];

    setlocale(LC_ALL, "rus");

    cout << "Введите строку: ";
    cin.getline(string, max_size);

    if (isPalindrome(string)) {
        cout << "Строка является палиндромом!" << endl;
    }
    else {
        cout << "Строка НЕ является палиндромом!" << endl;
    }

    return 0;
}