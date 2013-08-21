/*************************************
在平面上有一个圆，圆的边上按顺时针放着n个点。
现在要连m条边，可以从圆的内部连接，也可以从圆的外部连接。
给你的信息中，每个点最多只会连接的一条边。
问能不能连接这 m 条边，使这些边都不相交。
1：每个边看成2个点，分别表示在内部连接和在外部连接，只能选择一个。
2：如果两条边 i 和 j 必须一个画在内部，一个画在外部那么连边。
**************************************/

#include <stdio.h>
#include <iostream>
#include <stack>

const int maxn = 1011<<1;
const int maxm = 500011;
struct node{
    int u;
    int v;
    int next;
}edge[maxm], point[maxm];
std::stack<int>st;
int n, m, cnt, dfs_clock, scc_cnt;
int head[maxn], sccno[maxn], dfn[maxn], low[maxn];

void init(){
    cnt = 0;
    dfs_clock = 0;
    scc_cnt = 0;
    for(int i = 0; i <= n; i++){
        head[i] = -1;
        sccno[i] = 0;
        dfn[i] = 0;
        low[i] = 0;
    }
}

void add(int u, int v){
    edge[cnt].u = u;
    edge[cnt].v = v;
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
    if(low[u]==dfn[u]){
        ++scc_cnt;
        while(1){
            int x = st.top();
            st.pop();
            sccno[x] = scc_cnt;
            if(x==u) break;
        }
    }
}

int main(){
    while(~scanf("%d %d", &n, &m)){
        init();
        for(int i = 0; i < m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            if(u>v) std::swap(u, v);
            point[i].u = u;
            point[i].v = v;
        }
        for(int i = 0; i < m; i++){
            for(int j = i+1; j < m; j++){
                if((point[i].u<point[j].v && point[i].u>point[j].u && point[i].v>point[j].v)
                   ||(point[i].v<point[j].v && point[i].v>point[j].u && point[i].u<point[j].u)){
                        add(i<<1, j<<1|1);
                        add(j<<1, i<<1|1);
                        add(j<<1|1, i<<1);
                        add(i<<1|1, j<<1);
                }
            }
        }
        for(int i = 0; i < m<<1; i++){
            if(!dfn[i]) dfs(i);
        }
        bool flag = false;
        for(int i = 0; i < m; i++){
            if(sccno[i<<1]==sccno[i<<1|1]){
                flag = true;
                break;
            }
        }
        if(flag) puts("the evil panda is lying again");
        else puts("panda is telling the truth...");
    }
    return 0;
}
