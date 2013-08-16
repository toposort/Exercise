/************************************************
有一些昆虫，给出它们的配对关系，判断其中是否有虫子搞基。
*************************************************/

#include <stdio.h>
#include <string.h>

const int maxn = 10005;
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
    int t, k = 0;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        init();
        bool flag = false;
        for(int i = 0; i < m; i++){
            int u, v;
            scanf("%d %d", &u, &v);
            if(flag) continue;
            if(com[u]==-1){
                if(com[v]==-1){
                    com[u] = v;
                    com[v] = u;
                }
                else{
                    merge(u, com[v]);
                    com[u] = v;
                }
            }
            else{
                if(com[v]==-1){
                    merge(com[u], v);
                    com[v] = u;
                }
                else{
                    if(find(u)==find(v)) flag=true;
                    else{
                        merge(com[u], v);
                        merge(com[v], u);
                    }
                }
            }
        }
        printf("Scenario #%d:\n", ++k);
        if(flag) puts("Suspicious bugs found!\n");
        else puts("No suspicious bugs found!\n");
    }
    return 0;
}
