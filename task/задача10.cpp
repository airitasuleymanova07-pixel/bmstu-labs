#include <iostream>
using namespace std;
int main() {
	int a;
	setlocale(LC_ALL, "rus");
	cout << "������� �����:";
	cin >> a;
	if (a > 0) {  
        cout << "����� �������������" << endl;  
    }  
    else if (a < 0) {  
        cout << "����� �������������" << endl;  
    }  
    else {  
        cout << "����� ����� ����" << endl;  
    }  
    return 0;  
}  	
	


