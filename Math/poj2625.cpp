/***************************************
n种不同的coupons，每次得到每种coupons的概率相同;
求得到所有n种coupons的期望.
假设已有k种coupons，那么得到新的coupons的概率为(n-k)/n，
所以期望为n/(n-k)，结果为：n/n+n/(n-1)+...+n/1
****************************************/

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdlib.h>

int main(){
    int n;
    while(~scanf("%d", &n)){
        int p = 1, q = 1;
        for(int i = 1; i < n; i++){
            int l = p/std::__gcd(p, i)*i;
            q = l/p*q+l/i*n;
            p = l;
            l = std::__gcd(p, q);
            p /= l;
            q /= l;
        }
        int res = q/p;
        q = q%p;
        if(q==0) printf("%d\n", res);
        else{
            char s[101], s1[101], s2[101];
            sprintf(s, "%d", res);
            sprintf(s1, "%d", p);
            sprintf(s2, "%d", q);
            int len = strlen(s);
            int len1 = strlen(s1);
            int len2 = strlen(s2);
            for(int i = 0; i <= len; i++){
                printf(" ");
            }
            printf("%d\n", q);
            printf("%d ", res);
            for(int i = 0; i < std::max(len1, len2); i++){
                printf("-");
            }
            puts("");
            for(int i = 0; i <= len; i++){
                printf(" ");
            }
            printf("%d\n", p);
        }
    }
    return 0;
}
