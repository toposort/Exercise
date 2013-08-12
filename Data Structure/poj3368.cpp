/**************************************************
给定一个非降序的整数序列，对于一系列询问(l, r),
回答ai,ai+1...aj中出现次数最多的数的出现次数。
value[i]表示第 i 段的数值;
count[i]表示第 i 段的数值对应的出现次数;
num[p]表示位置 p 所在段的编号;
left[p]表示位置 p 所在段的左端点;
right[p]表示位置 p 所在段的右端点。
对于询问(l, r)，如果l和r在同一段中，结果为r-l+1;
否则为max(right[l]-l+1, r-left[r]+1, rmq(num[l]+1, num[r]-1))
***************************************************/

#include <stdio.h>
#include <iostream>
#include <math.h>

int n, q, cnt;
const int maxn = 100011;
int count[maxn], num[maxn], a[maxn], d[maxn][25];
int value[maxn], left[maxn], right[maxn];

void rmq_init(){
    for(int i = 1; i <= cnt; i++){
        d[i][0] = count[i];
    }
    for(int j = 1; (1<<j) <= cnt; j++){
        for(int i = 1; i+(1<<j)-1 <= cnt; i++){
            d[i][j] = std::max(d[i][j-1], d[i+(1<<(j-1))][j-1]);
        }
    }
}

int rmq(int l, int r){
    if(l>r) return -1;
    int k = (int)(log((double)(r-l+1))/log(2.0));
    int mmax = std::max(d[l][k], d[r-(1<<k)+1][k]);
    return mmax;
}

void init(){
    for(int i = 0; i <= n; i++){
        value[i] = 0;
        count[i] = 0;
        num[i] = 0;
        left[i] = 0;
        right[i] = 0;
    }
    cnt = 1;
    for(int i = 1; i <= n; i++){
        int numm = 1;
        num[i] = cnt;
        int l = i;
        while(a[i]==a[i+1]){
            ++numm;
            i++;
            if(i>n) break;
            num[i] = cnt;
        }
        int r = i;
        value[cnt] = a[i];
        count[cnt] = numm;
        num[i] = cnt++;
        for(int j = l; j <= r; j++){
            left[j] = l;
            right[j] = r;
        }
    }
}

int main(){
    while(~scanf("%d", &n)){
        if(n==0) break;
        scanf("%d", &q);
        for(int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
        }
        init();
        rmq_init();
        for(int i = 0; i < q; i++){
            int l, r;
            scanf("%d %d", &l, &r);
            if(num[l]==num[r]) printf("%d\n", r-l+1);
            else{
                int m1 = right[l]-l+1;
                int m2 = r-left[r]+1;
                int m3 = rmq(num[l]+1, num[r]-1);
                printf("%d\n", std::max(std::max(m1, m2), m3));
            }
        }
    }
    return 0;
}
