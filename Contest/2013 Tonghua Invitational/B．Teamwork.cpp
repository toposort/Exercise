/******************************************
给ｎ个位置和ｍ种工人，需要修复ｎ-1个位置，每个位置需要一定数量的每种工人。
给出每个位置修复的开始时间和持续时间，求最少需要派出多少工人。
首先根据每个位置修复的开始时间和持续时间求出开始时间和结束时间，
然后求出所有的位置需要工人的总数，对每种工人按照如下方式建图：
把每个位置拆为两个点，源点到第一个点连一条容量为需求工人数的边，
第二个点到汇点连一条容量为需求工人数的边，然后对于每个点枚举其他点，
如果可以从这个点到某个点（即Ｂ开始时间>=Ａ结束时间+路途时间），
那么连一条Ａ->Ｂ的容量为Ａ需求数的边。
最后对每种工人求一次最大流，用总数减去最大流最后结果即是答案。
*******************************************/

#include <string.h>
#include <stdio.h>
#include <iostream>
#define LL long long

const int maxn = 521;
const int maxm = maxn*maxn;
const int oo = 1<<29;
struct node{
    int u;
    int v;
    int w;
    int next;
}edge[maxm];
struct point{
    int x;
    int y;
    point(int _x=0, int _y=0):x(_x), y(_y){}
}p[maxn];
int n, m, cnt;
int head[maxn], b[maxn], e[maxn], map[maxn][6];
int cur[maxn], pre[maxn], dis[maxn], gap[maxn], aug[maxn];

void init(int n){
    cnt = 0;
    for(int i = 0; i <= n; i++){
        head[i] = -1;
    }
}

LL dist(point A, point B){
    return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
}

void add(int u, int v, int w){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
    edge[cnt].u = v;
    edge[cnt].v = u;
    edge[cnt].w = 0;
    edge[cnt].next = head[v];
    head[v] = cnt++;
}

int sap(int s, int e, int n){
    int max_flow = 0, u = s;
    int mindis;
    for(int i = 0; i <= n; i++){
        cur[i] = head[i];
        dis[i] = 0;
        gap[i] = 0;
    }
    aug[s] = oo;
    pre[s] = -1;
    gap[0] = n;
    while(dis[s]<n){
        bool flag = false;
        if(u==e){
            max_flow += aug[e];
            for(int v = pre[e]; v != -1; v = pre[v]){
                int id = cur[v];
                edge[id].w -= aug[e];
                edge[id^1].w += aug[e];
                aug[v] -= aug[e];
                if(edge[id].w==0) u = v;
            }
        }
        for(int id = cur[u]; id != -1; id = edge[id].next){
            int v = edge[id].v;
            if(edge[id].w>0 && dis[u]==dis[v]+1){
                flag = true;
                pre[v] = u;
                cur[u] = id;
                aug[v] = std::min(aug[u], edge[id].w);
                u = v;
                break;
            }
        }
        if(flag==false){
            if(--gap[dis[u]]==0) break;
            mindis = n;
            cur[u] = head[u];
            for(int id = head[u]; id != -1; id = edge[id].next){
                int v = edge[id].v;
                if(edge[id].w>0 && dis[v]<mindis){
                    mindis = dis[v];
                    cur[u] = id;
                }
            }
            dis[u] = mindis+1;
            ++gap[dis[u]];
            if(u!=s) u = pre[u];
        }
    }
    return max_flow;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        int x, y, sum = 0;
        scanf("%d %d", &x, &y);
        point st(x, y);
        for(int i = 1; i < n; i++){
            scanf("%d%d%d%d", &p[i].x, &p[i].y, &b[i], &e[i]);
            e[i] += b[i];
            for(int j = 0; j < m; j++){
                scanf("%d", &map[i][j]);
                sum += map[i][j];
            }
        }
        for(int k = 0; k < m; k++){
            init(n+n);
            int s = 0, t = n+n-1;
            for(int i = 1; i < n; i++){
                add(s, i, map[i][k]);
                add(i+n-1, t, map[i][k]);
                for(int j = 1; j < i; j++){
                    LL d = dist(p[i], p[j]);
                    if(b[j]>e[i] && d<=(b[j]-e[i])*(b[j]-e[i])) add(i, j+n-1, map[i][k]);
                    if(b[i]>e[j] && d<=(b[i]-e[j])*(b[i]-e[j])) add(j, i+n-1, map[j][k]);
                }
            }
            sum -= sap(s, t, n+n);
        }
        printf("%d\n", sum);
    }
    return 0;
}
