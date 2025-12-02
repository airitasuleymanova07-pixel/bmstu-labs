#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");

	ifstream infile("input.txt");

	if (infile.is_open()) {
		string line; //пременнная для хранения строки файла
		while (getline(infile, line)) {
			cout << line << endl;
		}
		infile.close();

	}
	else {
		cout << "Файл не найден, создаем его..." << endl;
		ofstream outfile("input.txt");
		if (outfile.is_open()) {
			outfile << "Это новый файл" << endl;
			outfile << "Привет, это вторая строчка" << endl;
			outfile << "дай бог, код сработает" << endl;
			outfile.close();
			cout << "Файл успешно (очень надеюсь) создан" << endl;
		}
		else {
			cout << "Файла нет((" << endl;
		}
	}
	return 0; //C:\Users\user\source\repos\work\work - путь к файлу 
}