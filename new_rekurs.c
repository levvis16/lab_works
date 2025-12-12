#include <stdio.h>
#include <stdlib.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int main() {
    printf("вы попали на сервер крутые червячки\n");
    int a, b;
    
    if (scanf("%d %d", &a, &b) != 2) {
        printf("ошибка: нужно ввести два целых числа\n");
        while (getchar() != '\n');
        return 1;
    }
    
    if (a == 0 && b == 0) {
        printf("ошибка: НОД(0,0) не определен\n");
        return 1;
    }
    
    int result = gcd(abs(a), abs(b));
    
    printf("%d\n", result);
    return 0;
} 
