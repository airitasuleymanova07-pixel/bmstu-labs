#include <iostream>  
#include <string>  
using namespace std;

int countVowels(const string& str) {
    int count = 0;
    
    string vowels = "aeiouAEIOU";   

    for (char c : str) {
        // ���������, �������� �� ������ �������  
        if (vowels.find(c) != string::npos) {
            count++;
        }
    }
    return count;
}

int main() {
    string input;
    setlocale(LC_ALL, "rus");
    cout << "������� ������: ";
    getline(cin, input); // ��������� ��� ������, ������� �������  

    int vowelCount = countVowels(input);
    cout << "���������� ������� ����: " << vowelCount << endl;

    return 0;
}
