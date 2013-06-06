/*************************************
n道题，解决第i题需要Ti时间。m个约束(ai,bi)，
要求题目ai要先于bi解决，保证Tai≤Tbi。
问 T 时间内最多解决的题目数量，同时罚时最少.
贪心，每次解决耗时最少的题目.
**************************************/
#include <stdio.h>

const int maxn = 1011;
const int maxm = 100011;
struct node{
    int u;
    int v;
    int next;
}edge[maxm];
int indegree[maxn], head[maxn], mem[maxn];
int time[maxn];
int n, m, t, cnt, num, res;

inline void init(){
    res = cnt = num = 0;
    for(int i = 0; i <= n; i++){
        indegree[i] = 0;
        head[i] = -1;
    }
}

inline void add(int u, int v){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

inline void solve(){
    int sum = 0;
    for(int j = 0; j < n; j++){
        int minn = 1<<28, loc;
        for(int i = 1; i <= n; i++){
            if(indegree[i]==0){
                if(minn > time[i]){
                    minn = time[i];
                    loc = i;
                }
            }
        }
        if(minn == 1<<28) return;
        if(sum+minn > t) return;
        sum += minn;
        res += sum;
        mem[num++] = loc;
        indegree[loc] = 1<<20;
        for(int i = head[loc]; i != -1; i = edge[i].next){
            int v = edge[i].v;
            --indegree[v];
        }
    }
}

int main(){
    while(~scanf("%d %d", &n, &t)){
        init();
        for(int i = 1; i <= n; i++){
            scanf("%d", &time[i]);
        }
        scanf("%d", &m);
        for(int i = 0; i < m; i++){
            int a, b;
            scanf("%d %d", &a, &b);
            add(a, b);
            indegree[b]++;
        }
        solve();
        printf("%d %d\n", num, res);
        if(num > 0){
            for(int i = 0; i < num-1; i++){
                printf("%d ", mem[i]);
            }
            printf("%d\n", mem[num-1]);
        }
    }
    return 0;
}
