/**************************************
求最少加多少条边构成边双连通图
如果两个点是在同一个边连通分量中，那么他们的low值是一样的
***************************************/
#include <stdio.h>
#include <string.h>
#include <iostream>

const int maxn = 5011;
const int maxm = 20011;
struct node{
    int u;
    int v;
    int next;
}edge[maxm];
int low[maxn], dfn[maxn], head[maxn], degree[maxn];
int n, m, cnt, dfs_clock;

void init(){
    cnt = 0;
    dfs_clock = 0;
    for(int i = 0; i <= n; i++){
        low[i] = 0;
        dfn[i] = 0;
        head[i] = -1;
        degree[i] = 0;
    }
}

void add(int u, int v){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u, int fa){
    low[u] = dfn[u] = ++dfs_clock;
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].v;
        if(!dfn[v]){
            dfs(v, u);
            low[u] = std::min(low[u], low[v]);
        }
        else if(dfn[v]<dfn[u] && v!=fa){
            low[u] = std::min(low[u], dfn[v]);
        }
    }
}

int main(){
    while(~scanf("%d %d", &n, &m)){
        init();
        for(int i = 0; i < m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
            add(v, u);
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]) dfs(i, -1);
        }
        for(int u = 1; u <= n; u++){
            for(int i = head[u]; i != -1; i = edge[i].next){
                int v = edge[i].v;
                if(low[u] != low[v]) ++degree[low[u]];
            }
        }
        int res = 0;
        for(int i = 1; i <= n; i++){
            if(1==degree[i]) res++;
        }
        printf("%d\n", (res+1)/2);
    }
    return 0;
}
