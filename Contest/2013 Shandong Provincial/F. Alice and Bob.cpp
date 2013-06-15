/****************************************
已知(a0*x^(2^0)+1)*(a1*x^(2^1)+1)*...*(an-1*x^(2^(n-1))+1).
给定a0,a1,...,an-1,和询问ｐ，求ｘ^p的系数。
*****************************************/

#include <stdio.h>
#include <string.h>
#include <iostream>
#define LL long long

const int maxn = 101;
const int mod = 2012;
int a[maxn];

int main(){
    int t, n, q;
    scanf("%d", &t);
    while(t--){
        memset(a, 0, sizeof(a));
        scanf("%d", &n);
        for(int i = 0; i < n; i++){
            scanf("%d", &a[i]);
        }
        scanf("%d", &q);
        while(q--){
            LL p;
            scanf("%lld", &p);
            int res = 1;
            for(int i = 0; ; i++){
                if(p&1){
                    res *= a[i];
                    res %= 2012;
                }
                p/=2;
                if(0==p) break;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
