#include <iostream>
using namespace std;
int main() {
    int n; 
    setlocale(LC_ALL, "rus");
    cout << "¬ведите число n: "; 
    cin >> n; 
    cout << " вадраты чисел от 1 до " << n << ":" << endl;
    for (int i = 1; i <= n; ++i) {
     cout << i << " * " << i << " = " << i * i << endl;
    }
    return 0; 
}