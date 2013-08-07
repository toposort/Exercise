/*************************************
给定一个字符串，求回文子串个数
用dp[i][j]表示这一段里有多少个回文串，首先dp[i][j]=dp[i+1][j]+dp[i][j-1]，
dp[i+1][j]和dp[i][j-1]可能有公共部分，要减去dp[i+1][j-1]。
如果str[i]==str[j]，要加上dp[j+1][i-1]+1，因为首尾可以组成一个回文子串，
而且首尾可以与中间任何一个回文子串组成新的回文子串.
**************************************/

#include <stdio.h>
#include <string.h>
#include <algorithm>

const int maxn = 1011;
const int mod = 10007;
char str[maxn];
int dp[maxn][maxn];

int main(){
    int t, k = 0;
    scanf("%d", &t);
    while(t--){
        k++;
        scanf("%s", str);
        int len = strlen(str);
        for(int i = 0; i < len; i++){
            dp[i][i] = 1;
        }
        for(int i = 1; i < len; i++){
            for(int j = i-1; j >= 0; j--){
                dp[j][i] = (dp[j+1][i]+dp[j][i-1]-dp[j+1][i-1]+mod)%mod;
                if(str[i] == str[j]){
                    dp[j][i] += (dp[j+1][i-1]+1);
                    dp[j][i] %= mod;
                }
            }
        }
        printf("Case %d: %d\n", k, dp[0][len-1]);
    }
    return 0;
}
