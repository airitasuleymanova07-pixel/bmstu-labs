#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;

int main() {
    setlocale(LC_ALL, "rus");

    const int MAX_SIZE = 100;
    char str1[MAX_SIZE], str2[MAX_SIZE];

    cout << "введите первую строку: ";
    cin.getline(str1, MAX_SIZE);

    cout << "введите вторую строку: ";
    cin.getline(str2, MAX_SIZE);

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int** dp = new int* [len1 + 1];
    for (int i = 0; i <= len1; i++) {
        dp[i] = new int[len2 + 1]();
    }

    int max_len = 0;    
    int end_pos = 0;    
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > max_len) {
                    max_len = dp[i][j];
                    end_pos = i - 1;
                }
            }
            else {
                dp[i][j] = 0;
            }
        }
    }

    if (max_len > 0) {
        cout << "самая длинная общая подстрока: \"";
        for (int i = end_pos - max_len + 1; i <= end_pos; i++) {
            cout << str1[i];
        }
        cout << "\"" << endl;
        cout << "длина: " << max_len << endl;
    }
    else {
        cout << "общих подстрок не найдено" << endl;
    }

    for (int i = 0; i <= len1; i++) {
        delete[] dp[i];
    }
    delete[] dp;

    return 0;
}