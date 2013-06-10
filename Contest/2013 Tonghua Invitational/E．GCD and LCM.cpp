/****************************************
给出Ｇ和Ｌ，求有多少个有序的三个整数<x,y,z>，使得gcd(x,y,z)=G,lcm(x,y,z)=L。
将L/G质数分解，x,y,z因子中至少一个数含有p1^a1，至少一个数不含p1;
所以对于p1而言方案数为C(3,1)+C(3,2)+(a1-1)*A(3,2)。
L/G = （A/G）*（B/G）
*****************************************/
#include <string.h>
#include <stdio.h>

const int maxn = 50001;
bool vis[maxn];
int prime[maxn];
int cnt;

void init(){
    cnt = 0;
    for(int i = 2; i < maxn; i++){
        if(!vis[i]){
            prime[cnt++] = i;
            for(int j = i; j <= maxn; j+=i){
                vis[j] = true;
            }
        }
    }
}

int main(){
    init();
    int t;
    scanf("%d", &t);
    while(t--){
        int g, l;
        scanf("%d %d", &g, &l);
        if(l%g){
            puts("0");
            continue;
        }
        l/=g;
        int res = 1;
        for(int i = 0; i < cnt; i++){
            if(prime[i]*prime[i] > l) break;
            if(l%prime[i]) continue;
            int num = 0;
            while(l%prime[i]==0){
                l /= prime[i];
                ++num;
            }
            res *=(3+3+(num-1)*6);
        }
        if(l>1) res*=(3+3+6*(1-1));
        printf("%d\n", res);
    }
    return 0;
}
