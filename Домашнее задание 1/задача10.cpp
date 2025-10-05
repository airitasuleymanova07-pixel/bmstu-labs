#include <iostream>
using namespace std;
int main() {
	int a;
	setlocale(LC_ALL, "rus");
	cout << "Введите число:";
	cin >> a;
	if (a > 0) {  
        cout << "Число положительное" << endl;  
    }  
    else if (a < 0) {  
        cout << "Число отрицательное" << endl;  
    }  
    else {  
        cout << "Число равно нулю" << endl;  
    }  
    return 0;  
}  	
	


