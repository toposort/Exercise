/**************************************
给定一个棋盘，上面已有一些其他棋子，现在要放置一些炮上去，
使得按照中国象棋的规则不能互相吃掉对方,问最多可以放多少个炮.
由于棋盘最大只有5×5, 直接暴力DFS即可。
***************************************/

#include <stdio.h>
#include <string.h>
#include <iostream>

const int maxn = 6;
int map[maxn][maxn];
int n, m, q, maxx;

void init(){
    maxx = -1;
    memset(map, 0, sizeof(map));
}

bool ok(int x, int y){
    int sum = 0, num = 0;
    for(int i = x-1; i >= 0; i--){
        if(map[i][y]==1){
            ++sum;
            ++num;
        }
        else if(map[i][y]==-1){
            if(sum==1 && num==1) return true;
            else if(sum == -1) return true;
            else if(sum == 0) --sum;
        }
    }
    sum = 0;
    num = 0;
    for(int i = y-1; i >= 0; i--){
        if(map[x][i]==1){
            ++sum;
            ++num;
        }
        else if(map[x][i]==-1){
            if(sum==1 && num==1) return true;
            else if(sum == -1) return true;
            else if(sum == 0) --sum;
        }
    }
    return false;
}

bool can(int x, int y){
    if(x<0 || x>n-1 || y<0 || y>m-1 || map[x][y]==1
       || map[x][y]==-1 || ok(x,y)) return false;
    return true;
}

void dfs(int x, int sum){
    if(x==n*m){
        maxx = std::max(sum, maxx);
        return;
    }
    int xx = x/m, yy = x%m;
    if(can(xx, yy)){
        map[xx][yy] = -1;
        dfs(x+1, sum+1);
        map[xx][yy] = 0;
    }
    dfs(x+1, sum);
}

int main(){
    while(~scanf("%d %d %d", &n, &m, &q)){
        init();
        for(int i = 0; i < q; i++){
            int u, v;
            scanf("%d %d",&u, &v);
            map[u][v] = 1;
        }
        dfs(0, 0);
        printf("%d\n", maxx);
    }
    return 0;
}
