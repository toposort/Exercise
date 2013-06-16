/********************************
给定一个有向图，判断是否对于任意两个点，都满足u->v或v->u
*********************************/

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <queue>

const int maxn = 2011;
const int maxm = 20011;
struct node{
    int u;
    int v;
    int next;
}edge[maxm];
int head[maxn];
bool vis[maxn], reach[maxn][maxn];
int n, m, cnt;

void init(){
    cnt = 0;
    memset(head, -1, sizeof(head));
    memset(reach, false, sizeof(reach));
}

void add(int u, int v){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
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
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].v;
            if(!vis[v]){
                qu.push(v);
                vis[v] = true;
                reach[s][v] = true;
            }
        }
    }
}

bool check(){
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            if(!(reach[i][j]||reach[j][i]) && i != j) return false;
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
            add(u, v);
        }
        for(int i = 1; i <= n; i++) bfs(i);
        if(check()) printf("Case %d: Kalimdor is just ahead\n", k);
        else printf("Case %d: The Burning Shadow consume us all\n", k);
    }
}
