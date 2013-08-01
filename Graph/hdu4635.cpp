/***********************************************
已知一个图，求使其不成为一个强连通图的前提下，最多可以加多少条边。
最终得到的图，肯定可以分成X和Y两部分，其中只有X到Y的边没有Y到X的边，
那么要使得边数尽可能的多，则X, Y肯定是一个完全图，X中每个点到Y的每个点都有边，
假设X有x个点，Y有y个点，所以边数F=x*y+x*(x-1)+y*(y-1)。
所以首先对于给定的有向图缩点，对于缩点后的每个点，如果它的出度或者入度为0，
那么它才有可能成为X或者Y，所以只要求缩点之后的出度或者入度为0的点中，包含节点数最少的
那个点，令它为其中一个部分，其它所有点加起来做另一个部分，就可以得到最多边数的图了。
************************************************/

#include <stdio.h>
#include <string.h>
#include <stack>
#include <iostream>
#include <vector>
#include <algorithm>
#define LL long long

const int maxn = 100011;
struct node{
    int u;
    int v;
    int next;
}edge[maxn];
int head[maxn], sccno[maxn], in[maxn], out[maxn];
int low[maxn], dfn[maxn], num[maxn], numm[maxn];
int n, m, cnt, scc_cnt, dfs_clock;
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
        num[i] = 0;
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
    int t, k = 0;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        init();
        k++;
        for(int i = 0; i < m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            add(u, v);
        }
        for(int i = 1; i <= n; i++){
            if(!dfn[i]) dfs(i);
        }
        if(scc_cnt==1){
            printf("Case %d: -1\n", k);
            continue;
        }
        for(int i = 1; i <= n; i++){
            int xx = sccno[i];
            num[xx]++;
            for(int j = head[i]; j != -1; j = edge[j].next){
                int v = edge[j].v;
                if(sccno[i] != sccno[v]){
                    out[sccno[i]]++;
                    in[sccno[v]]++;
                }
            }
        }
        LL minn = 1LL<<28;
        for(int i = 1; i <= scc_cnt; i++){
            if(in[i]==0 || out[i]==0){
                if(minn>num[i]) minn = num[i];
            }
        }
        int elsee = n-minn;
        LL res = (LL)elsee*(LL)(elsee-1);
        res += (LL)elsee*(LL)minn;
        res += (LL)minn*(LL)(minn-1);
        res -= m;
        printf("Case %d: %lld\n", k, res);
    }
    return 0;
}
