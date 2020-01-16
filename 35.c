#include <stdio.h>
int gcd(int a, int b) {
    if (a==0) {
        return b;
    }
    return gcd(b%a,a);
}
int main() {
    int i,t,num1, num2;
    int result1, result2;
    scanf("%d", &t);
    for (i=0; i<t; i++) {
        scanf("%d %d", &num1, &num2);
        result1=gcd(num1,num2);
        result2=(num1*num2)/result1;
        printf("%d ", result1);
        printf("%d\n", result2);
    }
    return 0;
}
