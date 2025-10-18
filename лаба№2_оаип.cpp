#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

// Функция для нахождения самой длинной общей подстроки
string longestCommonSubstring(const string& str1, const string& str2) {
    int m = str1.length();
    int n = str2.length();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    int maxLength = 0;
    int endPos = 0;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (str1[i - 1] == str2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > maxLength) {
                    maxLength = dp[i][j];
                    endPos = i - 1;
                }
            }
        }
    }

    if (maxLength == 0) return "";
    return str1.substr(endPos - maxLength + 1, maxLength);
}

int main() {
    string inputString;
    setlocale(LC_ALL, "rus");
    cout << "Введите строку из 10 слов на латинице: ";
    getline(cin, inputString);

    // Разделение строки на слова
    vector<string> words;
    stringstream ss(inputString);
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    // Проверка, что в строке ровно 10 слов
    if (words.size() != 10) {
        cout << "Ошибка: строка должна содержать ровно 10 слов!" << endl;
        cout << "Вы ввели " << words.size() << " слов." << endl;
        return 1;
    }

    cout << "\nИсходная строка: " << inputString << endl;
    cout << "Слова: ";
    for (const auto& w : words) {
        cout << w << " ";
    }
    cout << endl;

    // 1. Количество слов, начинающихся с буквы b
    int count_b = 0;
    for (const auto& word : words) {
        if (!word.empty() && tolower(word[0]) == 'b') {
            count_b++;
        }
    }
    cout << "\n1. Слов, начинающихся с 'b': " << count_b << endl;

    // 2. Длина самого длинного слова
    size_t max_length = 0;
    for (const auto& word : words) {
        if (word.length() > max_length) {
            max_length = word.length();
        }
    }
    cout << "2. Длина самого длинного слова: " << max_length << endl;

    // 3. Количество букв 'c' в третьем слове
    if (words.size() >= 3) {
        int count_c = 0;
        for (char c : words[2]) {
            if (tolower(c) == 'c') {
                count_c++;
            }
        }
        cout << "3. Количество букв 'c' в третьем слове ('" << words[2] << "'): " << count_c << endl;
    }

    // 4. Замена всех строчных букв на буквы верхнего регистра
    string uppercaseString = inputString;
    for (char& c : uppercaseString) {
        c = toupper(c);
    }
    cout << "4. Строка в верхнем регистре: " << uppercaseString << endl;

    // 5. Количество слов, у которых совпадает второй и предпоследний символ
    int count_matching = 0;
    for (const auto& word : words) {
        if (word.length() >= 4) { // Нужно как минимум 4 символа для второго и предпоследнего
            if (word[1] == word[word.length() - 2]) {
                count_matching++;
            }
        }
    }
    cout << "5. Слов с совпадающими вторым и предпоследним символом: " << count_matching << endl;

    // 6. Самая длинная общая подстрока между двумя словами в предложении
    string longestSubstring = "";
    string wordPair = "";

    for (size_t i = 0; i < words.size(); i++) {
        for (size_t j = i + 1; j < words.size(); j++) {
            string common = longestCommonSubstring(words[i], words[j]);
            if (common.length() > longestSubstring.length()) {
                longestSubstring = common;
                wordPair = words[i] + " и " + words[j];
            }
        }
    }

    if (!longestSubstring.empty()) {
        cout << "6. Самая длинная общая подстрока: '" << longestSubstring << "'" << endl;
        cout << "   Найдена между словами: " << wordPair << endl;
        cout << "   Длина: " << longestSubstring.length() << endl;
    }
    else {
        cout << "6. Общих подстрок не найдено" << endl;
    }

    return 0;
}