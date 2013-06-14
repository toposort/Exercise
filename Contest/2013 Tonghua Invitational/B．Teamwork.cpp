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

int sap(int S, int T, int N){
    int maxflow = 0;
    int pre[maxn], dis[maxn] = {}, gap[maxn] = {}, cur[maxn];
    std::copy(head, head+N, cur);
    gap[0] = N+1;
    ++gap[dis[S]=1];
    for(int u = pre[S]=S; dis[S] <= N; ++gap[++dis[u]],u=pre[u]){
        for(bool flag = true; flag; ){
            flag = false;
            for(int &p = cur[u]; ~p; p = edge[p].next){
                if(!edge[p].w || dis[u]!=dis[edge[p].v]+1) continue;
                flag = true;
                pre[edge[p].v] = u;
                u = edge[p].v;
                if(u==T){
                    int aug = oo;
                    for(int i = S; i != T; i = edge[cur[i]].v){
                        if(aug > edge[cur[i]].w){
                            u = i;
                            aug = edge[cur[i]].w;
                        }
                    }
                    for(int i = S; i != T; i = edge[cur[i]].v){
                        edge[cur[i]].w -= aug;
                        edge[cur[i]^1].w += aug;
                    }
                    maxflow += aug;
                }
                break;
            }
        }
        if(--gap[dis[u]]==0) break;
        dis[u] = N;
        for(int i = head[u]; ~i; i = edge[i].next){
            if(edge[i].w && dis[u] > dis[edge[i].v]){
                dis[u] = dis[edge[i].v];
                cur[u] = i;
            }
        }
    }
    return maxflow;
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
