#include <iostream>  
using namespace std;

int main() {
    int n;
    long long sum = 0;   
    cout << "������� ����� n: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0 || i % 5 == 0) {
            sum += i;
        }
    }
    cout << "����� ����� �� 1 �� " << n << ", ��������� �� 2 ��� 5: " << sum << endl;
    return 0;
}