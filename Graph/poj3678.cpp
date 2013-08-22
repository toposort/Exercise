#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stack>

const int maxn = 10011;
const int maxm = 500011;
struct node{
    int u;
    int v;
    int next;
}edge[maxm];
std::stack<int>st;
int n, m, cnt, dfs_clock, scc_cnt;
int head[maxn], sccno[maxn], dfn[maxn], low[maxn];

void init(){
    while(!st.empty()) st.pop();
    cnt = 0;
    dfs_clock = 0;
    scc_cnt = 0;
    for(int i = 0; i <= n*2; i++){
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
            int u, v, w;
            char s[21];
            scanf("%d %d %d %s", &u, &v, &w, s);
            if(s[0]=='A'){
                if(w==0){
                    add(u<<1|1, v<<1);
                    add(v<<1|1, u<<1);
                }
                else if(w==1){
                    add(u<<1, u<<1|1);
                    add(v<<1, v<<1|1);
                    add(u<<1|1, v<<1|1);
                    add(v<<1|1, u<<1|1);
                }
            }
            else if(s[0]=='O'){
                if(w==0){
                    add(u<<1, v<<1);
                    add(v<<1, u<<1);
                    add(u<<1|1, u<<1);
                    add(v<<1|1, v<<1);
                }
                else if(w==1){
                    add(u<<1, v<<1|1);
                    add(v<<1, u<<1|1);
                }
            }
            else if(s[0]=='X'){
                if(w==0){
                    add(u<<1, v<<1);
                    add(v<<1, u<<1);
                    add(u<<1|1, v<<1|1);
                    add(v<<1|1, u<<1|1);
                }
                else if(w==1){
                    add(u<<1, v<<1|1);
                    add(v<<1|1, u<<1);
                    add(u<<1|1, v<<1);
                    add(v<<1, u<<1|1);
                }
            }
        }
        for(int i = 0; i < n+n; i++){
            if(!dfn[i]) dfs(i);
        }
        bool flag = false;
        for(int i = 0; i < n; i++){
            if(sccno[i<<1]==sccno[i<<1|1]){
                flag = true;
                break;
            }
        }
        if(flag) puts("NO");
        else puts("YES");
    }
    return 0;
}
