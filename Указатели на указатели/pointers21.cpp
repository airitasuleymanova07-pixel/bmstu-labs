#include <stdio.h>

void swapPointers(int** a, int** b) {
    int* temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int x = 10, y = 20;
    int* p1 = &x, * p2 = &y;

    printf("До обмена:\n");
    printf("p1 = %p, *p1 = %d\n", (void*)p1, *p1);
    printf("p2 = %p, *p2 = %d\n", (void*)p2, *p2);
    printf("x = %d, y = %d\n", x, y);

    swapPointers(&p1, &p2);

    printf("\nПосле обмена:\n");
    printf("p1 = %p, *p1 = %d\n", (void*)p1, *p1);
    printf("p2 = %p, *p2 = %d\n", (void*)p2, *p2);
    printf("x = %d, y = %d\n", x, y);

    return 0;
}