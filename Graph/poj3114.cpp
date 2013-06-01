/*******************************************
给出n个城市，m条边.如果从A能到B，从B也能到A，
他们的通信时间为0. 求从 s 到 t 最短的通信时间.
********************************************/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <queue>

const int oo = 1<<28;
const int maxn = 521;
const int maxm = maxn*maxn;
struct node{
    int v;
    int w;
    int next;
}edge[maxm];
int head[maxn], dfn[maxn], low[maxn], sccno[maxn];
int n, m, cnt, scc_cnt, dfs_clock;
int dis[maxn], vis[maxn];
std::stack<int>st;

void init(){
    cnt = 0;
    scc_cnt = 0;
    dfs_clock = 0;
    for(int i = 0; i <= n; i++){
        head[i] = -1;
        dfn[i] = 0;
        low[i] = 0;
        sccno[i] = 0;
    }
}

void add(int u, int v, int w){
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}


void dfs(int u){
    low[u] = dfn[u] = ++dfs_clock;
    st.push(u);
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].v;
        if(!dfn[v]){
            dfs(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if(!sccno[v]){
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        ++scc_cnt;
        while(1){
            int x = st.top();
            st.pop();
            sccno[x] = scc_cnt;
            if(x==u) break;
        }
    }
}

void spfa(int s){
    for(int i = 0; i <= n; i++){
        vis[i] = false;
        dis[i] = oo;
    }
    std::queue<int>qu;
    qu.push(s);
    vis[s] = true;
    dis[s] = 0;
    while(!qu.empty()){
        int u = qu.front();
        qu.pop();
        vis[u] =false;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].v;
            int w = edge[i].w;
            if(sccno[u] == sccno[v]) w = 0;
            if(dis[u]+w < dis[v]){
                dis[v] = dis[u]+w;
                if(!vis[v]){
                    vis[v] = true;
                    qu.push(v);
                }
            }
        }
    }
}

int main(){
    while(~scanf("%d %d", &n, &m)){
        if(0==n && 0==m) break;
        init();
        for(int i = 0; i < m; i++){
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w);
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]) dfs(i);
        }
        int q;
        scanf("%d", &q);
        while(q--){
            int s, t;
            scanf("%d %d", &s, &t);
            if(sccno[s] == sccno[t]){
                puts("0");
                continue;
            }
            else{
                spfa(s);
                if(dis[t]>=oo) puts("Nao e possivel entregar a carta");
                else printf("%d\n", dis[t]);
            }
        }
        puts("");
    }
    return 0;
}
