/***********************************
给定一个有向图，判断是否对于任意两个点，都满足u->v或v->u
************************************/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>

const int maxn = 2011;
const int maxm = 20011;
const int oo = 1<<29;
struct node{
    int u;
    int v;
    int next;
}edge[maxm], edge1[maxm];
int indegree[maxn], head1[maxn];
int head[maxn], low[maxn], dfn[maxn], sccno[maxn];
int n, m, cnt, dfs_clock, scc_cnt;
std::stack<int>st;

void init(){
    cnt = 0;
    dfs_clock = 0;
    scc_cnt = 0;
    for(int i = 0; i <= n; i++){
        head[i] = -1;
        head1[i] = -1;
        low[i] = 0;
        dfn[i] = 0;
        sccno[i] = 0;
        indegree[i] = 0;
    }
}

void add(int u, int v, int head[], struct node edge[]){
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

bool topo(){
    for(int k = 0; k < scc_cnt; k++){
        int num = 0, u;
        for(int i = 1; i <= scc_cnt; i++){
            if(indegree[i]==0){
                ++num;
                u = i;
                indegree[i] = oo;
            }
        }
        if(num != 1) return false;
        for(int i = head1[u]; i != -1; i = edge1[i].next){
            int v = edge1[i].v;
            --indegree[v];
        }
    }
    return true;
}

int main(){
    int t, k = 0;
    scanf("%d", &t);
    while(t--){
        ++k;
        scanf("%d %d", &n, &m);
        init();
        for(int i = 0; i < m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v, head, edge);
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]) dfs(i);
        }
        cnt = 0;
        for(int u = 1; u <= n; u++){
            for(int i = head[u]; i != -1; i = edge[i].next){
                int v = edge[i].v;
                if(sccno[u] != sccno[v]){
                    add(sccno[u], sccno[v], head1, edge1);
                    ++indegree[sccno[v]];
                }
            }
        }
        if(topo()) printf("Case %d: Kalimdor is just ahead\n", k);
        else printf("Case %d: The Burning Shadow consume us all\n", k);
    }
    return 0;
}
