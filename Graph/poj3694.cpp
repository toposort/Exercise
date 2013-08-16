/**************************************
一个无向图，q个操作，每次在两个点间连接一条边，每次连接后整个无向图还剩下多少桥
一个图求一次边双连通分量缩点后将变成一颗树或者森林，并且树中的每条边都是桥
***************************************/

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

const int maxn = 100005;
const int maxm = maxn<<2;
struct node{
    int u;
    int v;
    int next;
}edge[maxm];
int n, m, cnt, dfs_clock, bridge_cnt;
int low[maxn], dfn[maxn], set[maxn];
int head[maxn], father[maxn];

void init(){
    cnt = 0;
    dfs_clock = 0;
    bridge_cnt = 0;
    for(int i = 0; i <= n; i++){
        head[i] = -1;
        low[i] = 0;
        dfn[i] = 0;
        set[i] = i;
        father[i] = 0;
    }
}

void add(int u, int v){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int find(int x){
    if(set[x] != x) set[x] = find(set[x]);
    return set[x];
}

bool merge(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fy != fx){
        set[fy] = fx;
        return true;
    }
    return false;
}

void dfs(int u, int fa){
    low[u] = dfn[u] = ++dfs_clock;
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].v;
        if(!dfn[v]){
            dfs(v, u);
            father[v] = u;
            low[u] = std::min(low[u], low[v]);
            if(low[v] > dfn[u]) ++bridge_cnt;
            else merge(u, v);
        }
        else if(dfn[v]<dfn[u] && v!=fa){
            low[u] = std::min(low[u], dfn[v]);
        }
    }
}

void lca(int u, int v){
    while(u != v){
        while(dfn[u]>=dfn[v] && u!=v){
            if(merge(u, father[u])) --bridge_cnt;
            u = father[u];
        }
        while(dfn[v]>=dfn[u] && u!=v){
            if(merge(v, father[v])) --bridge_cnt;
            v = father[v];
        }
    }
}

int main(){
    int k = 0;
    while(~scanf("%d %d", &n, &m)){
        if(n==0 && m==0) break;
        init();
        while(m--){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
            add(v, u);
        }
        dfs(1, -1);
        int q;
        scanf("%d", &q);
        printf("Case %d:\n", ++k);
        while(q--){
            int u, v;
            scanf("%d %d", &u, &v);
            lca(u, v);
            printf("%d\n", bridge_cnt);
        }
        puts("");
    }
    return 0;
}
