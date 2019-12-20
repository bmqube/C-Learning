#include <stdio.h>

int main() {
    int n;
    for (n=1; n<=5000; n++) {
        if (n%4==0) {
            if(n%100!=0 || n%400==0) {
                 printf("%d\n", n);
            }
        }
    }
    return 0;
}
