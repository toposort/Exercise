/*******************************************
有 m 层楼，从 一 层到 m 层，要进入每层都要打开位于该层的两道门中的至少一道。
门锁有2 n 种,每个门锁为 2n 种中的一种，可以重复.有2n把钥匙，分别对应2n种锁;
钥匙两两一组,每组只能选一个来开门,被选中的可以多次使用,另一个不能用,最多能上多少层。
********************************************/

#include <stdio.h>
#include <iostream>
#include <stack>
#include <string.h>

const int maxn = 1111<<2;
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
    for(int i = 0; i <= n*4; i++){
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
        if(n==0 && m==0) break;
        init();
        for(int i = 0; i < n; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u<<1, v<<1|1);
            add(v<<1, u<<1|1);
        }
        int res = 0;
        bool flag = true;
        for(int i = 0; i < m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            if(flag){
                add(u<<1|1, v<<1);
                add(v<<1|1, u<<1);
                memset(dfn, 0, sizeof(dfn));
                memset(sccno, 0, sizeof(sccno));
                dfs_clock = 0;
                scc_cnt = 0;
                for(int j = 0; j < 4*n; j++){
                    if(!dfn[j]) dfs(j);
                }
                for(int j = 0; j < n+n; j++){
                    if(sccno[j<<1]==sccno[j<<1|1]){
                        flag = false;
                        break;
                    }
                }
                if(flag) res++;
            }
            else continue;
        }
        printf("%d\n", res);
    }
    return 0;
}
