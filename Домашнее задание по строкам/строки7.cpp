#include <iostream>
#include <cstring>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 256;
    char input[MAX_SIZE];
    char output[MAX_SIZE * 2] = "";

    cout << "введите строку: ";
    cin.getline(input, MAX_SIZE);

    int input_len = strlen(input);
    int output_index = 0;

    int i = 0;
    while (i < input_len) {
        char current_char = input[i];
        int count = 1;

        while (i + count < input_len && input[i + count] == current_char) {
            count++;
        }

        output[output_index++] = current_char;

        if (count > 1) {
            char count_str[10];
            int num_len = 0;
            int temp = count;

            while (temp > 0) {
                count_str[num_len++] = '0' + (temp % 10);
                temp /= 10;
            }

            for (int j = num_len - 1; j >= 0; j--) {
                output[output_index++] = count_str[j];
            }
        }
        else {
            output[output_index++] = '1';
        }

        i += count;
    }

    output[output_index] = '\0';

    cout << "сжатая строка: " << output << endl;

    return 0;
}