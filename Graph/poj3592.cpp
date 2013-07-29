/***************************************
给定一个矩阵，左上角为起点，每个格子都有一定价值的金矿
（#表示岩石，不可达，*表示时空门，可以到达指定格子）
要求最多可以获得多大利益.有了时空门后图会出现环
求强联通分量进行缩点，对缩点后的图建立有向无环图，然后求最长路.
****************************************/

#include <stdio.h>
#include <string.h>
#include <queue>
#include <stack>
#include <iostream>

const int maxn = 2011;
const int maxm = maxn<<2;
const int oo = -1<<29;
struct node{
    int u;
    int v;
    int w;
    int next;
}edge1[maxm], edge2[maxm];
int n, m, cnt, scc_cnt, dfs_clock;
int vis[maxn], dis[maxn];
int low[maxn], dfn[maxn], sccno[maxn];
int head1[maxn], head2[maxn], val[maxn];
std::stack<int>st;

bool isdigit(char c){
    if(c>='0' && c<='9') return true;
    return false;
}

void init(){
    cnt = 0;
    scc_cnt = 0;
    dfs_clock = 0;
    memset(low, 0, sizeof(low));
    memset(dfn, 0, sizeof(dfn));
    memset(val, 0, sizeof(val));
    memset(sccno, 0, sizeof(sccno));
    memset(head1, -1, sizeof(head1));
    memset(head2, -1, sizeof(head2));
}

void add(int u, int v, int w, struct node edge[], int head[]){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u){
    low[u] = dfn[u] = ++dfs_clock;
    st.push(u);
    for(int i = head1[u]; i != -1; i = edge1[i].next){
        int v = edge1[i].v;
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
    for(int i = 0; i <= n*m; i++){
        vis[i] = 0;
        dis[i] = oo;
    }
    std::queue<int>qu;
    dis[s] = 0;
    vis[s] = 1;
    qu.push(s);
    while(!qu.empty()){
        int u = qu.front();
        qu.pop();
        vis[u] = 0;
        for(int i = head2[u]; i != -1; i = edge2[i].next){
            int v = edge2[i].v;
            int w = edge2[i].w;
            if(dis[u]+w > dis[v]){
                dis[v] = dis[u]+w;
                if(!vis[v]){
                    qu.push(v);
                    vis[v] = 1;
                }
            }
        }
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        init();
        char mapp[101][101];
        std::cin>>n>>m;
        for(int i = 0; i < n; i++){
            std::cin>>mapp[i];
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++)
            if(mapp[i][j] != '#'){
                if(i) add((i-1)*m+j, i*m+j , 0, edge1, head1);
                if(j) add(i*m+j-1, i*m+j, 0, edge1, head1);
                if(mapp[i][j]=='*'){
                    int x, y;
                    scanf("%d %d", &x, &y);
                    if(mapp[x][y]!='#') add(i*m+j, x*m+y, 0, edge1, head1);
                }
            }
        }
        for(int i = 0; i < n*m; i++){
            if(!dfn[i]) dfs(i);
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < m; j++){
                if(mapp[i][j]!='*' && mapp[i][j]!='#'){
                    int no = sccno[i*m+j];
                    val[no] += mapp[i][j]-'0';
                }
            }
        }
        for(int u = 0; u < n*m; u++){
            for(int i = head1[u]; i != -1; i = edge1[i].next){
                int v = edge1[i].v;
                if(sccno[u] != sccno[v]){
                    add(sccno[u], sccno[v], val[sccno[v]], edge2, head2);
                }
            }
        }
        spfa(sccno[0]);
        int maxx = -1;
        for(int i = 1; i <= scc_cnt; i++){
            if(dis[i] > maxx) maxx = dis[i];
        }
        printf("%d\n", maxx+val[sccno[0]]);
    }
    return 0;
}
