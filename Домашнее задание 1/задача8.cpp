#include <iostream>  
#include <string>  
using namespace std;

int countVowels(const string& str) {
    int count = 0;
    
    string vowels = "aeiouAEIOU";   

    for (char c : str) {
        // проверяем, является ли символ гласной  
        if (vowels.find(c) != string::npos) {
            count++;
        }
    }
    return count;
}

int main() {
    string input;
    setlocale(LC_ALL, "rus");
    cout << "Введите строку: ";
    getline(cin, input); // считываем всю строку, включая пробелы  

    int vowelCount = countVowels(input);
    cout << "Количество гласных букв: " << vowelCount << endl;

    return 0;
}
