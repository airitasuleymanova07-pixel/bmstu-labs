#include <iostream>
//using namespace std;
int main()
{
    float a;
    std::cin >> a;
    if (a > 50) {
        std::cout << "������� ����������" << std::endl;
    }
    else if (a < 20) {
        std::cout << "������� �� ������, ������ �����������!" << std::endl;
    }
    else {
        std::cout << "������������� ��������" << std::endl;
    }
    return 0;
}