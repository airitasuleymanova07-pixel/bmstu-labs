#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {

	ofstream file("text.txt");
	if (file.is_open()) {
		file << "It's already three o'clock in the morning" << endl;
		file << "I'm still doing my homework" << endl;
		file << "I hope you're not reading this" << endl;
		file << "I want to go to Ufa already" << endl;
		file << "Okay, I like Baumanka" << endl;
		file << "But I already want to go home" << endl;
		file << "I want to close descriptive geometry by 4" << endl;
	}
	else {
		cout << "File could not be created" << endl;
	}

	ifstream infile("text.txt");

	if (infile.is_open()) {
		string word;
		int countword = 0;

		while (infile >> word) {
			countword++;
		}
		cout << "All words:" << countword << endl;
		infile.close();
	}
	else {
		cout << "The file could not be opened" << endl;
	}
	return 0;
}
