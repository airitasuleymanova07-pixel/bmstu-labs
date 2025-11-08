#include <iostream>
#include <locale>

using namespace std;

void myStrCat(char* dest, const char* src) {
    while (*dest != '\0') {
        dest++;
    }

    while (*src != '\0') {
        *dest = *src;  
        dest++;        
        src++;        
    *dest = '\0'; 
}

int main() {
    setlocale(LC_ALL, "rus");  

    const int MAX_LENGTH = 100;
    char dest[MAX_LENGTH];
    char src[MAX_LENGTH];
   
    cout << "¬ведите первую строку (dest): ";
    cin.getline(dest, MAX_LENGTH);
    
    cout << "¬ведите вторую строку (src): ";
    cin.getline(src, MAX_LENGTH);
    myStrCat(dest, src);
    cout << "\n–езультат конкатенации: \"" << dest << "\"" << endl;

    return 0;
}