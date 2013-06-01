/***********************************
山东省第二届省赛题
1000个点20000条边的有向图，每次询问如果把其中一条边变为无向边后
该图的包含点最多的强联通分量包含的点数。
tarjan 求一遍原图的强连通分量，然后缩点后枚举起点bfs出reach[][]
表示两点是否可达，然后枚举所有点，如果reach[x][i] && reach[i][y] 那么，num+=scccn[i]，
最后输出 max(num, scc_max).
************************************/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>
#include <queue>

const int maxn = 1011;
const int maxm = 20011;
struct node{
    int u;
    int v;
    int next;
}edge[maxm], edge1[maxn];
int n, m, cnt, scc_cnt, dfs_clock, scc_max;
int head[maxn], dfn[maxn], low[maxn], sccno[maxn];
bool reach[maxn][maxn], vis[maxn];
int scccn[maxn];
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
        scccn[i] = 0;
    }
    memset(reach, false, sizeof(reach));
}

void add(int u, int v){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void add1(int u, int v){
    edge1[cnt].u = u;
    edge1[cnt].v = v;
    edge1[cnt].next = head[u];
    head[u] = cnt++;
}

void bfs(int s){
    std::queue<int>qu;
    memset(vis, false, sizeof(vis));
    qu.push(s);
    while(!qu.empty()){
        int u = qu.front();
        qu.pop();
        vis[u] = true;
        for(int i = head[u]; i != -1; i = edge1[i].next){
            int v = edge1[i].v;
            if(!vis[v]){
                qu.push(v);
                vis[v] = true;
                reach[s][v] = true;
            }
        }
    }
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

int query(int i){
    int u = edge[i-1].u;
    int v = edge[i-1].v;
    int ui = sccno[u];
    int vi = sccno[v];
    int ret;
    if(ui == vi) ret = scc_max;
    else{
        for(int i = 0; i <= scc_cnt; i++){
            vis[i] = false;
        }
        ret = scccn[ui] + scccn[vi];
        vis[ui] = true;
        vis[vi] = true;
        for(int i = 1; i <= scc_cnt; i++){
            if(reach[ui][i] && reach[i][vi]){
                if(!vis[i]){
                    ret += scccn[i];
                    vis[i] = true;
                }
            }
        }
    }
    return std::max(ret, scc_max);
}

int main(){
    int t, q;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d %d", &n, &m, &q);
        init();
        for(int i = 0; i < m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]) dfs(i);
        }
        cnt = 0;
        memset(head, -1, sizeof(head));
        for(int i = 0; i < m; i++){
            int u = edge[i].u;
            int v = edge[i].v;
            if(sccno[u] != sccno[v]) add1(sccno[u], sccno[v]);
        }
        for(int i = 1; i <= scc_cnt; i++){
            bfs(i);
        }
        for(int i = 1; i <= n; i++){
            int x = sccno[i];
            ++scccn[x];
        }
        scc_max = -1;
        for(int i = 1; i <= n; i++){
            scc_max = std::max(scc_max, scccn[i]);
        }
        for(int i = 0; i < q; i++){
            int u;
            scanf("%d", &u);
            int res = query(u);
            printf("%d\n", res);
        }
    }
    return 0;
}
