/*****************************************
两个帮派，给出一些互相敌对的点对，判断某两个点之间的关系
因为开始无法确定两个点分别属于哪个帮派，所以无法直接并查集，
用com[u] = v 表示和 u 敌对的点为 v，对于输入的两个点u，v：
merge(u, com[v]), merge(v, com[u]);
******************************************/

#include <stdio.h>
#include <string.h>

const int maxn = 1e5+11;
int n, m;
int father[maxn], com[maxn];

void init(){
    for(int i = 0; i <= n; i++){
        father[i] = i;
        com[i] = -1;
    }
}

int find(int x){
    if(x==father[x]) return x;
    father[x] = find(father[x]);
    return father[x];
}

void merge(int x, int y){
    int fx = find(x);
    int fy = find(y);
    if(fx != fy) father[fx] = fy;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        init();
        for(int i = 0; i < m; i++){
            int u, v;
            getchar();
            char c;
            scanf("%c %d %d", &c, &u, &v);
            if(c=='D'){
                if(com[u]==-1) com[u] = v;
                if(com[v]==-1) com[v] = u;
                merge(u, com[v]);
                merge(v, com[u]);
            }
            else{
                if(find(u)==find(v)) puts("In the same gang.");
                else if(find(u)==find(com[find(v)])
                        || find(v)==find(com[find(u)])) puts("In different gangs.");
                else puts("Not sure yet.");
            }
        }
    }
    return 0;
}
