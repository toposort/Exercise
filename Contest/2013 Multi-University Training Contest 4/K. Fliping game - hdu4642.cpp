/************************************
不管从哪个格子开始翻，总会翻到右下角的那个格子。
所以如果右下角格子为1的话，翻奇数次可以翻成0，
如果右下角格子为0，翻偶数次可以翻成0。
所以初始的时候右下角为1则Alice胜，否则Bob胜。
*************************************/

#include <stdio.h>

const int maxn = 111;
int a[maxn][maxn];

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        int n, m;
        scanf("%d %d", &n, &m);
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= m; j++){
                scanf("%d", &a[i][j]);
            }
        }
        if(a[n][m]) puts("Alice");
        else puts("Bob");
    }
    return 0;
}
