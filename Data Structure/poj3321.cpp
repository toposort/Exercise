/****************************************
一棵具有n个节点的树，每个节点上都有一个苹果。
给出 m 组操作：
C i：摘掉第 i 个节点上面的苹果,若不存在，则加一个苹果;
Q i:查询以第 i 个节点为根的子树有几个苹果。
****************************************/

#include <stdio.h>
#include <iostream>
#include <string.h>

const int maxn = 100011;
int c[maxn], head[maxn];
int n, m, cnt, dfs_clock;
int start[maxn], end[maxn];
bool vis[maxn];
struct node{
    int u;
    int v;
    int next;
}edge[maxn<<1];

void addedge(int u, int v){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

int lowbit(int x){
    return x&(-x);
}

void add(int x, int delta){
    for(int i = x; i <= n; i += lowbit(i)){
        c[i] += delta;
    }
}

int getsum(int x){
    int sum = 0;
    for(int i = x; i > 0; i -= lowbit(i)){
        sum += c[i];
    }
    return sum;
}

void init(){
    cnt = 0;
    dfs_clock = 0;
    for(int i = 1; i <= n; i++){
        head[i] = -1;
        add(i, 1);
        vis[i] = false;
    }
}

void dfs(int s){
    start[s] = ++dfs_clock;
    vis[s] = true;
    for(int i = head[s]; i != -1; i = edge[i].next){
        int v = edge[i].v;
        if(!vis[v]) dfs(v);
    }
    end[s] = dfs_clock;
}

int main(){
    scanf("%d", &n);
    init();
    for(int i = 0; i < n-1; i++){
        int u, v;
        scanf("%d %d", &u, &v);
        addedge(u, v);
        addedge(v, u);
    }
    dfs(1);
    scanf("%d", &m);
    while(m--){
        getchar();
        char ch;
        int s;
        scanf("%c %d", &ch, &s);
        if(ch=='C'){
            int delta;
            int ret = getsum(start[s])-getsum(start[s]-1);
            if(ret==1) delta = -1;
            else delta = 1;
            add(start[s], delta);
        }
        else{
            printf("%d\n", getsum(end[s])-getsum(start[s]-1));
        }
    }
    return 0;
}
