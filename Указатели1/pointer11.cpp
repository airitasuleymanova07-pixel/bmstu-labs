#include <iostream>

using namespace std;

int myStrCmp(const char* s1, const char* s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}

int main() {
    const char* str1 = "hello";
    const char* str2 = "world";
    const char* str3 = "hello";
    const char* str4 = "hell";

    cout << "Compare '" << str1 << "' and '" << str2 << "': " << myStrCmp(str1, str2) << endl;
    cout << "Compare '" << str2 << "' and '" << str1 << "': " << myStrCmp(str2, str1) << endl;
    cout << "Compare '" << str1 << "' and '" << str3 << "': " << myStrCmp(str1, str3) << endl;
    cout << "Compare '" << str1 << "' and '" << str4 << "': " << myStrCmp(str1, str4) << endl;

    return 0;
}
