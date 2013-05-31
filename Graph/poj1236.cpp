
/***********************************************
学校之间有单向的网络，每个学校得到一套软件后，可以通过单向网络向周边的学校传输.
1:初始至少需要向多少个学校发放软件，使得网络内所有的学校最终都能得到软件。
2:至少需要添加几条传输线路，使任意向一个学校发放软件后，经过传送，所有学校都能得到软件。
************************************************/

#include <stdio.h>
#include <string.h>
#include <stack>
#include <iostream>

const int maxn = 111;
const int maxm = maxn*maxn;
struct node{
    int u;
    int v;
    int next;
}edge[maxm];
int head[maxn], sccno[maxn], in[maxn], out[maxn];
int low[maxn], dfn[maxn];
bool iscut[maxn];
int n, cnt, scc_cnt, dfs_clock;
std::stack<int>st;

void init(){
    cnt = 0;
    scc_cnt = 0;
    dfs_clock = 0;
    for(int i = 0; i <= n; i++){
        low[i] = 0;
        dfn[i] = 0;
        head[i] = -1;
        sccno[i] = 0;
        in[i] = 0;
        out[i] = 0;
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
    while(~scanf("%d", &n)){
        init();
        for(int i = 1; i <= n; i++){
            while(1){
                scanf("%d", &m);
                if(0==m) break;
                add(i, m);
            }
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]) dfs(i);
        }
        for(int i = 1; i <= n; i++){
            for(int j = head[i]; j != -1; j = edge[j].next){
                int v = edge[j].v;
                if(sccno[i] != sccno[v]){
                    out[sccno[i]]++;
                    in[sccno[v]]++;
                }
            }
        }
        if(scc_cnt==1){
            puts("1\n0");
            continue;
        }
        int resa = 0, resb = 0;
        for(int i = 1; i <= scc_cnt; i++){
            if(!in[i]) resa++;
            if(!out[i]) resb++;
        }
        printf("%d\n%d\n", resa, std::max(resa, resb));
    }
    return 0;
}
