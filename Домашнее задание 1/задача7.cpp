#include <iostream>
using namespace std;
int main() {
    int n; 
    setlocale(LC_ALL, "rus");
    cout << "������� ����� n: "; 
    cin >> n; 
    cout << "�������� ����� �� 1 �� " << n << ":" << endl;
    for (int i = 1; i <= n; ++i) {
     cout << i << " * " << i << " = " << i * i << endl;
    }
    return 0; 
}