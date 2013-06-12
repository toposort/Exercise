#include <stdio.h>
#include <cmath>
#include <string>
#include <iostream>

const int maxn = 111;
struct node{
    std::string name;
    int num;
}team[maxn];

int main(){
    int t;
    scanf("%d", &t);
    while (t--){
        int n, s, x, y, mod;
        int counter = 0;
        scanf("%d %d %d %d %d", &n, &s, &x, &y, &mod);
        for (int i = 1; i <= n; i++){
            std::string t1, t2;
            std::cin>>team[i].name>>t1>>team[i].num>>t2;
        }
        for (int i = 1; i <= n; i++){
            if(counter+team[i].num > s){
                std::cout<<s-counter<<" pages for "<<team[i].name<<std::endl;
                counter = 0;
                s = (s*x+y)%mod;
                i--;
            }
            else{
                std::cout<<team[i].num<<" pages for "<<team[i].name<<std::endl;
                counter += team[i].num;
            }
        }
        printf("\n");
    }
    return 0;
}
