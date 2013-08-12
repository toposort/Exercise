#include <stdio.h>
#include <iostream>
#include <string.h>

const int maxn = 110;
const int oo = 1<<29;
int map[maxn][maxn], dis[maxn][maxn];
int pre[maxn][maxn], res[maxn];
int n, m, cnt, mincircle;

void init(){
    mincircle = oo+1;
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= n; j++){
            dis[i][j] = oo;
            map[i][j] = 0;
            pre[i][j] = -1;
        }
        dis[i][i] = 0;
        map[i][i] = 0;
    }
}

void floyd(){
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= k; i++){
            for(int j = 1; j <= k; j++){
                if(map[i][k]&&map[k][j]&&i!=j){
                    int tmp = dis[i][j]+map[j][k]+map[k][i];
                    if(tmp < mincircle){
                        mincircle = tmp;
                        cnt = 1;
                        res[0] = k;
                        int p = i;
                        while(p!=-1){
                            res[cnt++] = p;
                            p = pre[p][j];
                        }
                    }
                }
            }
        }
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                if(dis[i][j] > dis[i][k]+dis[k][j]){
                    dis[i][j] = dis[i][k]+dis[k][j];
                    pre[i][j] = pre[i][k];
                }
            }
        }
    }
}

int main(){
    while(~scanf("%d %d", &n, &m)){
        init();
        for(int i = 0; i < m; i++){
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            if(w < dis[u][v]){
                map[u][v]=map[v][u]=dis[u][v]=dis[v][u]=w;
            }
            pre[u][v] = v;
            pre[v][u] = u;
        }
        floyd();
        if(mincircle>=oo) puts("No solution.");
        else{
            printf("%d", res[0]);
            for(int i = 1; i < cnt; i++){
                printf(" %d", res[i]);
            }
            puts("");
        }
    }
    return 0;
}
