#include <iostream>  
using namespace std;

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Код | Символ" << endl;
    cout << "----|--" << endl;
    for (int r = 32; r <= 126; r++) {
        cout << r << "   | " << static_cast<char>(r) << endl;
    }

    return 0;
}