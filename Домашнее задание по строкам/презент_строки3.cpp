#include <iostream>
#include <cstring>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char text[MAX_SIZE];
    char search[MAX_SIZE];
    char replace[MAX_SIZE];
    char result[MAX_SIZE * 2] = ""; 
    cout << "введите исходную строку: ";
    cin.getline(text, MAX_SIZE);

    cout << "введите подстроку для поиска: ";
    cin.getline(search, MAX_SIZE);

    cout << "введите строку для замены: ";
    cin.getline(replace, MAX_SIZE);

    int text_len = strlen(text);
    int search_len = strlen(search);
    int replace_len = strlen(replace);
    int result_index = 0;

    for (int i = 0; i < text_len; ) {
        bool found = true;
        for (int j = 0; j < search_len; j++) {
            if (i + j >= text_len || text[i + j] != search[j]) {
                found = false;
                break;
            }
        }

        if (found && search_len > 0) {
            for (int k = 0; k < replace_len; k++) {
                result[result_index++] = replace[k];
            }
            i += search_len; 
        }
        else {
            result[result_index++] = text[i];
            i++;
        }
    }

    result[result_index] = '\0';

    cout << "результат: " << result << endl;

    return 0;
}