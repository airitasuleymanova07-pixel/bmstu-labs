#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int* p = &vec[0];
    int sum = 0;
    size_t size = vec.size();

    for (size_t i = 0; i < size; i++) {
        sum += *p;
        p++;
    }

    cout << "Sum: " << sum << endl;

    return 0;
}