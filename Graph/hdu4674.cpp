/*************************************
给定一个无向图，并且保证每个点最多只在一个简单环上，
询问是否存在一条从u到v且要经过w的路径，每个点只走一次。
**************************************/

#include <stdio.h>
#include <iostream>
#include <queue>
#include <stack>
#include <string.h>

const int maxn = 100011;
const int maxm = 150000<<1;
struct node{
    int u;
    int v;
    bool vis;
    int next;
}edge[maxm], edge1[maxm];
int n, m, cnt, dfs_clock, bcc_cnt;
int head[maxn], head1[maxn], d[maxn], p[maxn][21];
int dfn[maxn], low[maxn], bccno[maxn];
std::stack<int>st;

void init(){
    cnt = 0;
    bcc_cnt = 0;
    dfs_clock = 0;
    while(!st.empty()) st.pop();
    for(int i = 0; i <= n; i++){
        head[i] = -1;
        head1[i] = -1;
        low[i] = 0;
        dfn[i] = 0;
        bccno[i] = 0;
        d[i] = 0;
    }
}

void add(int u, int v, int head[], struct node edge[]){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].vis = false;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void tarjan(int u){
    dfn[u] = low[u] = ++dfs_clock;
    st.push(u);
    for(int i = head[u]; i != -1; i = edge[i].next){
        if(edge[i].vis) continue;
        edge[i].vis = edge[i^1].vis = 1;
        int v = edge[i].v;
        if(!dfn[v]){
            tarjan(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if(!bccno[v]) low[u] = std::min(low[u], dfn[v]);
    }
    if(low[u]==dfn[u]){
        ++bcc_cnt;
        while(1){
            int v = st.top();
            st.pop();
            bccno[v]=bcc_cnt;
            if(u==v) break;
        }
    }
}

void dfs(int u, int fa){
    d[u] = d[fa]+1;
    p[u][0] = fa;
    for(int i = 1; i < 18; i++){
        p[u][i] = p[p[u][i-1]][i-1];
    }
    for(int i = head1[u]; i != -1; i = edge1[i].next){
        int v = edge1[i].v;
        v = bccno[v];
        if(v == fa) continue;
        dfs(v, u);
    }
}

int lca(int a, int b){
    if(d[a] > d[b]) std::swap(a, b);
    if(d[a] < d[b]){
        int k = d[b]-d[a];
        for(int i = 0; i < 18; i++){
            if(k&(1<<i)) b = p[b][i];
        }
    }
    if(a != b){
        for(int i = 17; i >= 0; i--){
            if(p[a][i] != p[b][i]){
                a = p[a][i];
                b = p[b][i];
            }
        }
        a = p[a][0];
        b = p[b][0];
    }
    return a;
}

int swim(int a, int b){
    int k = d[a]-d[b]-1;
    for(int i = 0; i < 18; i++){
        if(k&(1<<i)) a = p[a][i];
    }
    return a;
}

int judge(int u, int v){
    for(int i = head1[u]; i != -1; i = edge1[i].next){
        int vv = edge1[i].v;
        if(bccno[vv]==bccno[v]) return vv;
    }
    return -1;
}

int main(){
    while(~scanf("%d %d", &n, &m)){
        if(n==0 && m==0) break;
        init();
        while(m--){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v, head, edge);
            add(v, u, head, edge);
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]) tarjan(i);
        }
        cnt = 0;
        for(int u = 1; u <= n; u++){
            for(int i = head[u]; i != -1; i = edge[i].next){
                int v = edge[i].v;
                if(bccno[u] != bccno[v]){
                    add(bccno[u], v, head1, edge1);
                }
            }
        }
        d[1] = 0;
        dfs(1, 1);
        scanf("%d", &m);
        while(m--){
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            int uu = bccno[u], vv = bccno[v], ww = bccno[w];
            int uv = lca(uu, vv), uw = lca(uu, ww), vw = lca(vv, ww);
            if(u==v){
                if(u==w) puts("Yes");
                else puts("No");
            }
            else if(u==w || v==w) puts("Yes");
            else if(uu==vv){
                if(uu==ww) puts("Yes");
                else puts("No");
            }
            else if(uu==ww){
                int ret;
                if(uv==uu){
                    vv = swim(vv, ww);
                    ret = judge(vv, u);
                }
                else ret = judge(p[uu][0], u);
                if(ret!=u) puts("Yes");
                else puts("No");
            }
            else if(vv==ww){
                int ret;
                if(uv==vv){
                    uu = swim(uu, ww);
                    ret = judge(uu, v);
                }
                else ret = judge(p[vv][0],v);
                if(ret!=v) puts("Yes");
                else puts("No");
            }
            else{
                if(uv==uw && vw==ww){
                    int ret1, ret2;
                    vv = swim(vv, ww);
                    ret1 = judge(vv, w);
                    if(uv==ww){
                        uu = swim(uu, ww);
                        ret2 = judge(uu, w);
                    }
                    else ret2 = judge(p[ww][0],w);
                    if(ret1!=w && ret2!=w && ret1==ret2) puts("No");
                    else puts("Yes");
                }
                else if(uv==vw && uw==ww){
                    int ret1, ret2;
                    uu = swim(uu, ww);
                    ret1 = judge(uu, w);
                    if(uv==ww){
                        vv = swim(vv, ww);
                        ret2 = judge(vv, w);
                    }
                    else ret2 = judge(p[ww][0],w);
                    if(ret1!=w && ret2!=w && ret1==ret2) puts("No");
                    else puts("Yes");
                }
                else puts("No");
            }
        }
    }
    return 0;
}
