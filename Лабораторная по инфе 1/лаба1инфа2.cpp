# include <iostream>
int main1()
{
	int a;
	std::cin >> a;
	while (a >= 0) {
		std::cout << "������� ���������� ������" << std::endl;
		std::cin >> a;
		if (a < 0) {
			break;
		}
	}
}