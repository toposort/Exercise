/************************************
有n种插座,m种电器,每种插座一个,插座只能插一个电器(或者适配器).每种电器只能插在一种插座上
有k种适配器，每种适配器可以有无限多数量,每种适配器(a, b)可以把b类插座变为a类插座
问最后有多少个电器无法使用.建图求最大流即可,建图方案:
各个电器各自为一个节点,和源点相连,容量为1, 将室内已有的插座各自为一个节点,和汇点相连,容量为1
将电器到其应该插的插座类型的点做边,容量为1, 将适配器(a, b)从a点到b点连边,容量为oo
*************************************/

#include <stdio.h>
#include <map>
#include <string>
#include <iostream>
#include <string.h>

const int maxn = 1011;
const int maxm = 100011;
const int oo = 1<<29;

struct Arclist{
    int cnt, head[maxn], dis[maxn];
    int cur[maxn], pre[maxn], gap[maxn], aug[maxn];
    struct node{int u, v, w, next;}edge[maxm];
    void init(int n){cnt = 0; std::fill_n(head, n+1, -1);}
    void add(int u, int v, int w){
        edge[cnt].u = u;edge[cnt].v = v;
        edge[cnt].w = w;edge[cnt].next = head[u];
        head[u] = cnt++;edge[cnt].u = v;
        edge[cnt].v = u;edge[cnt].w = 0;
        edge[cnt].next = head[v];head[v] = cnt++;
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
}G;

int main(){
    int n, m, k, id = 1;
    std::map<std::string, int>mp;
    std::map<std::string, int>mp1;
    char s[maxn][11];
    scanf("%d", &n);
    G.init(500);
    for(int i = 0; i < n; i++){
        getchar();
        scanf("%s", s[i]);
        ++mp1[s[i]];
    }
    scanf("%d", &m);
    for(int i = 1; i <= n; i++){
        mp[s[i-1]] = m+i;
    }
    id = m+n+1;
    for(int i = 1; i <= m; i++){
        getchar();
        G.add(0, i, 1);
        char s1[maxn], s2[maxn];
        scanf("%s %s", s1, s2);
        mp[s1] = i;
        if(mp[s2]==0) mp[s2] = id++;
        G.add(i, mp[s2], 1);
    }
    scanf("%d", &k);
    for(int i = 0; i < k; i++){
        getchar();
        char s1[maxn], s2[maxn];
        scanf("%s %s", s1, s2);
        if(mp[s1]==0) mp[s1] = id++;
        if(mp[s2]==0) mp[s2] = id++;
        G.add(mp[s1], mp[s2], oo);
    }
    for(int i = 1; i <= n; i++){
        G.add(m+i, id, mp1[s[i-1]]);
    }
    int res = G.sap(0, id, id+1);
    printf("%d\n", m-res);
    return 0;
}
