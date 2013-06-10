/******************************
求12个数的平均值，结果保留两位小数并去掉最后的0
*******************************/
#include <string.h>
#include <stdio.h>
int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        char s[1001];
        double sum = 0;
        for(int i = 0; i < 12; i++){
            double u;
            scanf("%lf", &u);
            sum += u;
        }
        sum/=12;
        sprintf(s, "%.2f", sum);
        int len = strlen(s);
        for(int i = len-1; i >= 0; i--){
            if(s[i] != '0') break;
            s[i] = 0;
        }
        len = strlen(s);
        int i, cnt = 0;
        printf("$");
        for(i = 0; i < len; i++){
            if(s[i]=='.') break;
            printf("%c", s[i]);
        }
        if(len-i>=2){
            for(int j = i; j < len && cnt<=2; j++, cnt++){
                printf("%c", s[j]);
            }
        }
        puts("");
    }
}
