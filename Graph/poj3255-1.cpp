/*************************************
求次短路：
分别以起点和终点为源点作两次spfa, 次短路必定是dis1[u]+w+dis2[v]
枚举所有边。找到满足dis1[u]+w+dis2[v] > dis1[n]条件下的最小值
***************************************/

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <queue>

const int oo = 1<<29;
const int maxn = 5011;
const int maxm = 100011<<1;
struct node{
    int u;
    int v;
    int w;
    int next;
}edge[maxm];
int n, m, cnt;
int head[maxn], dis1[maxn], dis2[maxn];
bool vis[maxn];
std::queue<int>qu;

void init(){
    cnt = 0;
    for(int i = 0; i <= n; i++){
        head[i] = -1;
        dis1[i] = oo;
        dis2[i] = oo;
        vis[i] = false;
    }
}

void add(int u, int v, int w){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void spfa(int s, int dis[]){
    dis[s] = 0;
    qu.push(s);
    vis[s] = true;
    while(!qu.empty()){
        int u = qu.front();
        qu.pop();
        vis[u] = false;
        for(int i = head[u]; i != -1; i = edge[i].next){
            int v = edge[i].v;
            int w = edge[i].w;
            if(dis[u]+w < dis[v]){
                dis[v] = dis[u]+w;
                if(!vis[v]){
                    qu.push(v);
                    vis[v] = true;
                }
            }
        }
    }
}

int main(){
    while(~scanf("%d %d", &n, &m)){
        init();
        for(int i = 0; i < m; i++){
            int u, v, w;
            scanf("%d %d %d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }
        spfa(1, dis1);
        memset(vis, false, sizeof(vis));
        spfa(n, dis2);
        int res = oo;
        for(int i = 0; i < cnt; i++){
            int u = edge[i].u;
            int v = edge[i].v;
            int w = edge[i].w;
            int temp = dis1[u]+w+dis2[v];
            if(temp>dis1[n] && temp<res) res = temp;
        }
        printf("%d\n", res);
    }
    return 0;
}
