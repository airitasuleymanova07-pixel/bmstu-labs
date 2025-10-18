#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

using namespace std;

// ������� ��� ���������� ����� ������� ����� ���������
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
    cout << "������� ������ �� 10 ���� �� ��������: ";
    getline(cin, inputString);

    // ���������� ������ �� �����
    vector<string> words;
    stringstream ss(inputString);
    string word;

    while (ss >> word) {
        words.push_back(word);
    }

    // ��������, ��� � ������ ����� 10 ����
    if (words.size() != 10) {
        cout << "������: ������ ������ ��������� ����� 10 ����!" << endl;
        cout << "�� ����� " << words.size() << " ����." << endl;
        return 1;
    }

    cout << "\n�������� ������: " << inputString << endl;
    cout << "�����: ";
    for (const auto& w : words) {
        cout << w << " ";
    }
    cout << endl;

    // 1. ���������� ����, ������������ � ����� b
    int count_b = 0;
    for (const auto& word : words) {
        if (!word.empty() && tolower(word[0]) == 'b') {
            count_b++;
        }
    }
    cout << "\n1. ����, ������������ � 'b': " << count_b << endl;

    // 2. ����� ������ �������� �����
    size_t max_length = 0;
    for (const auto& word : words) {
        if (word.length() > max_length) {
            max_length = word.length();
        }
    }
    cout << "2. ����� ������ �������� �����: " << max_length << endl;

    // 3. ���������� ���� 'c' � ������� �����
    if (words.size() >= 3) {
        int count_c = 0;
        for (char c : words[2]) {
            if (tolower(c) == 'c') {
                count_c++;
            }
        }
        cout << "3. ���������� ���� 'c' � ������� ����� ('" << words[2] << "'): " << count_c << endl;
    }

    // 4. ������ ���� �������� ���� �� ����� �������� ��������
    string uppercaseString = inputString;
    for (char& c : uppercaseString) {
        c = toupper(c);
    }
    cout << "4. ������ � ������� ��������: " << uppercaseString << endl;

    // 5. ���������� ����, � ������� ��������� ������ � ������������� ������
    int count_matching = 0;
    for (const auto& word : words) {
        if (word.length() >= 4) { // ����� ��� ������� 4 ������� ��� ������� � ��������������
            if (word[1] == word[word.length() - 2]) {
                count_matching++;
            }
        }
    }
    cout << "5. ���� � ������������ ������ � ������������� ��������: " << count_matching << endl;

    // 6. ����� ������� ����� ��������� ����� ����� ������� � �����������
    string longestSubstring = "";
    string wordPair = "";

    for (size_t i = 0; i < words.size(); i++) {
        for (size_t j = i + 1; j < words.size(); j++) {
            string common = longestCommonSubstring(words[i], words[j]);
            if (common.length() > longestSubstring.length()) {
                longestSubstring = common;
                wordPair = words[i] + " � " + words[j];
            }
        }
    }

    if (!longestSubstring.empty()) {
        cout << "6. ����� ������� ����� ���������: '" << longestSubstring << "'" << endl;
        cout << "   ������� ����� �������: " << wordPair << endl;
        cout << "   �����: " << longestSubstring.length() << endl;
    }
    else {
        cout << "6. ����� �������� �� �������" << endl;
    }

    return 0;
}