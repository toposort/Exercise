#include <stdio.h>
#include <iostream>
#include <string.h>

const int maxn = 1111;
int c[maxn][maxn];
int s, id;

int lowbit(int x){
    return x&(-x);
}

void add(int x, int y, int delta){
    for(int i = x; i <= s; i += lowbit(i)){
        for(int j = y; j <= s; j += lowbit(j)){
            c[i][j] += delta;
        }
    }
}

int getsum(int x, int y){
    int sum = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        for(int j = y; j > 0; j -= lowbit(j)){
            sum += c[i][j];
        }
    }
    return sum;
}

int main(){
    while(~scanf("%d", &id)){
        if(id==0){
            scanf("%d", &s);
            memset(c, 0, sizeof(c));
        }
        else if(id==1){
            int x, y, a;
            scanf("%d %d %d", &x, &y, &a);
            add(x+1, y+1, a);
        }
        else if(id==2){
            int l, b, r, t;
            scanf("%d %d %d %d", &l, &b, &r, &t);
            ++l;++b;++r;++t;
            int res = getsum(r, t)-getsum(l-1, t)-getsum(r, b-1)+getsum(l-1, b-1);
            printf("%d\n", res);
        }
        else return 0;
    }
    return 0;
}
