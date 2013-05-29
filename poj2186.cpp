/***********
n头奶牛，给出若干个欢迎关系（a, b），表示a欢迎b，
欢迎关系是单向的，但是是可以传递的。另外每个奶牛都是欢迎他自己的。
求出被所有的奶牛欢迎的奶牛的数目。
************/
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stack>

const int maxn = 100011;
const int maxm = 500011;
struct node{
    int u;
    int v;
    int next;
}edge[maxm];
int head[maxn], low[maxn], dfn[maxn];
bool iscut[maxn];
int n, m, cnt, dfs_clock, scc_cnt;
int sccno[maxn], out[maxn];
std::stack<int>st;

void init(){
    cnt = 0;
    dfs_clock = 0;
    scc_cnt = 0;
    for(int i = 0; i <= n; i++){
        head[i] = -1;
        out[i] = 0;
        dfn[i] = 0;
        low[i] = 0;
        sccno[i] = 0;
        iscut[i] = false;
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

int main(){
    while(~scanf("%d%d", &n, &m)){
        init();
        for(int i = 0; i < m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]) dfs(i);
        }
        for(int i = 1; i <= n; i++){
            for(int j = head[i]; j != -1; j = edge[j].next){
                int v = edge[j].v;
                if(sccno[i] != sccno[v]){
                    out[sccno[i]]++;
                }
            }
        }
        int sum = 0;
        int loc = 0;
        for(int i = 1; i <= scc_cnt; i++){
            if(!out[i]){
                sum++;
                loc = i;
            }
        }
        if(sum != 1) puts("0");
        else{
            int res = 0;
            for(int i = 1; i <= n; i++){
                if(sccno[i] == loc) res++;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
