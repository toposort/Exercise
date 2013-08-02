/**********************************
dp[i]表示0-i这段区间可能变成的不同句子数，
dp[i+1]+=dp[i]，如向后连续4个字符是hehe，
那么dp[i+4]+=dp[i]，最后的答案就是dp[len]了
***********************************/

#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>

const int mod = 10007;
const int maxn = 10111;
int dp[maxn];
std::string s;

int main(){
    int t, k = 0;
    scanf("%d", &t);
    while(t--){
        k++;
        std::cin>>s;
        memset(dp, 0, sizeof(dp));
        dp[0] = 1;
        int len = s.size();
        for(int i = 0; i < len; i++){
            dp[i] %= mod;
            dp[i+1] += dp[i];
            if(s[i]=='h' && s[i+1]=='e' && s[i+2]=='h' && s[i+3]=='e'){
                dp[i+4] += dp[i];
            }
        }
        printf("Case %d: %d\n", k, dp[len]%mod);
    }
    return 0;
}

