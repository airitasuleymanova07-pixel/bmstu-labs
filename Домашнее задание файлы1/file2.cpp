#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
	setlocale(LC_ALL, "rus");
	ofstream file("data.txt");
	if (file.is_open()) {
		file << "Интересно этот код сработает" << endl;
		file << "Файл он создаст, а я его потом точно не найду" << endl;
		file << "И удалить не смогу, память заполнится" << endl;
		file << "Да и код не сработает наверное, тысячу раз буду исправлять" << endl;
		file << "Да и уже заберут меня в уфу походу" << endl;
		file << "Потому что у меня выходит три по начерту в дипломе" << endl;
	}
	else {
		cout << "Файл не удалось создать" << endl;
	}
	ifstream infile("data.txt");
	if (infile.is_open()) {
		string line;
		int countstr = 0;

		while (getline(infile, line)) {
			countstr++;
			cout << "Строка" << countstr << endl;
		}
		cout << "Всего строк:" << countstr << endl;
		file.close();
	}
	else {
		cout << "Файл не удалось открыть((" << endl;
	}
	return 0;
}
