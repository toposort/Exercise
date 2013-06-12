/**********************************************
给两叠数量相同的牌，两人轮流取，只能从顶部或者底部取牌，
每次只能取一张，每张牌上有分数，问先手最多能得多少分。
记忆化搜搜索。dp[a][b][c][d]表示当前的第1堆牌顶部为第a张，
底部为第b张时, 第2堆牌顶部为第c张，底部为第d张时, 先手最多能获得的分数.
dp[a][b][c][d]=sum-min(dp[a+1][b][c][d],dp[a][b-1][c][d],dp[a][b][c+1][d],dp[a][b][c][d-1]);
***********************************************/

#include <string.h>
#include <stdio.h>
#include <iostream>

const int maxn = 25;
int aa[maxn], bb[maxn];
int dp[maxn][maxn][maxn][maxn];

void init(){
    memset(dp, 0, sizeof(dp));
}

int dfs(int a, int b, int c, int d, int sum){
    if(a>b && c>d) return 0;
    if(dp[a][b][c][d]) return dp[a][b][c][d];
    if(c < d){
        dp[a][b][c][d] = sum-std::min(dfs(a+1, b, c, d, sum-aa[a]), dfs(a, b-1, c, d, sum-aa[b]));
    }
    else if(a < b){
        dp[a][b][c][d] = sum-std::min(dfs(a, b, c+1, d, sum-bb[c]), dfs(a, b, c, d-1, sum-bb[d]));
    }
    else{
        dp[a][b][c][d] = sum-std::min(std::min(dfs(a+1, b, c, d, sum-aa[a]), dfs(a, b-1, c, d, sum-aa[b])),
                                    std::min(dfs(a, b, c+1, d, sum-bb[c]), dfs(a, b, c, d-1, sum-bb[d])));
    }
    return dp[a][b][c][d];
}

int main(){
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        init();
        int sum = 0;
        for(int i = 1; i <= n; i++){
            scanf("%d", &aa[i]);
            sum += aa[i];
        }
        for(int i = 1; i <= n; i++){
            scanf("%d", &bb[i]);
            sum += bb[i];
        }
        printf("%d\n", dfs(1, n, 1, n, sum));
    }
    return 0;
}
