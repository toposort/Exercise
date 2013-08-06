/**************************************
给一个 1~n 的排列，问区间[l, r]间有多少段连续的数.
先对询问按右端点 y 从左到右排序，然后从左到右扫描整个数列，
插入一个数x：
如果x+1和x-1都已出现，那么x的插入会使得他们3个数连成一段，段的个数减少1；
如果两者均没有出现，那么段的个数增加1；如果只出现其一，则段的个数不发生变化；
***************************************/

#include <stdio.h>
#include <algorithm>
#define lowbit(x) ((x)&(-x))

const int maxn = 100011;
struct node{
    int x;
    int y;
    int id;
    bool operator <(const node & a)const{
        return y < a.y;
    }
}edge[maxn];

int n, m;
bool vis[maxn];
int num[maxn], sum[maxn], ans[maxn], pos[maxn];

void init(){
    for(int i = 0; i <= n; i++){
        sum[i] = 0;
        vis[i] = false;
    }
}

void update(int x, int val){
    while(x <= n){
        sum[x] += val;
        x += lowbit(x);
    }
}

int getsum(int x){
    int ret = 0;
    while(x > 0){
        ret += sum[x];
        x -= lowbit(x);
    }
    return ret;
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &n, &m);
        init();
        for(int i = 1; i <= n; i++){
            scanf("%d", &num[i]);
            pos[num[i]] = i;
        }
        for(int i = 0; i < m; i++){
            scanf("%d %d", &edge[i].x, &edge[i].y);
            edge[i].id = i;
        }
        std::sort(edge, edge+m);
        for(int i = 1, k = 0; i <= n; i++){
            update(i, 1);
            if(vis[num[i]-1]) update(pos[num[i]-1], -1);
            if(vis[num[i]+1]) update(pos[num[i]+1], -1);
            vis[num[i]] = 1;
            for( ; edge[k].y==i && k < m; k++){
                ans[edge[k].id] = getsum(edge[k].y)-getsum(edge[k].x-1);
            }
            if(k==m) break;
        }
        for(int i = 0; i < m; i++){
            printf("%d\n", ans[i]);
        }
    }
    return 0;
}
