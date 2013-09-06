/********************************************
* 找可行解的方案就是：
* 根据第一次建的图建一个反图..然后求逆拓扑排序..
* 建反图的原因是保持冲突的两个事件肯定会被染成不同的颜色..
* 求逆拓扑排序的原因也是为了对图染的色不会发生冲突..
* 输出可行解就是遍历一次逆拓扑排序时染成的颜色..
* 输出同一组颜色的解就是其中的一组可行解..
*********************************************/

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <stack>
#include <queue>

const int maxn = 2011;
const int maxm = 3000011;
struct node{
    int u;
    int v;
    int next;
}edge1[maxm], edge2[maxm];
struct tt{
    int s;
    int e;
    int l;
}tim[maxn];
int n, m, cnt1, cnt2, scc_cnt, dfs_clock;
int head1[maxn], head2[maxn], in[maxn], ct[maxn], ans[maxn];
int sccno[maxn], dfn[maxn], low[maxn], color[maxn];
std::stack<int>st;

void init(){
    cnt1 = 0;
    cnt2 = 0;
    scc_cnt = 0;
    dfs_clock = 0;
    memset(in, 0, sizeof(in));
    memset(ans, 0, sizeof(ans));
    memset(color, 0, sizeof(color));
    memset(sccno, 0, sizeof(sccno));
    memset(dfn, 0, sizeof(dfn));
    memset(low, 0, sizeof(low));
    memset(head1, -1, sizeof(head1));
    memset(head2, -1, sizeof(head2));
}

void add(int u, int v, struct node edge[], int head[], int &cnt){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

void dfs(int u){
    low[u] = dfn[u] = ++dfs_clock;
    st.push(u);
    for(int i = head1[u]; i != -1; i = edge1[i].next){
        int v = edge1[i].v;
        if(!dfn[v]){
            dfs(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if(!sccno[v]){
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if(low[u]==dfn[u]){
        ++scc_cnt;
        while(1){
            int x = st.top();
            st.pop();
            sccno[x] = scc_cnt;
            if(x==u) break;
        }
    }
}

void toposort(){
    std::queue<int>qu;
    for(int i = 1; i <= scc_cnt; i++){
        if(in[i]==0) qu.push(i);
    }
    while(!qu.empty()){
        int u = qu.front();
        qu.pop();
        if(color[u]==0){
            color[u] = 1;
            color[ct[u]] = -1;
        }
        for(int i = head2[u]; i != -1; i = edge2[i].next){
            int v = edge2[i].v;
            --in[v];
            if(in[v]==0) qu.push(v);
        }
    }
}

int main(){
    while(~scanf("%d", &n)){
        init();
        for(int i = 0; i < n; i++){
            int s1, s2, t1, t2, l;
            int sb = scanf("%d:%d %d:%d %d", &s1, &s2, &t1, &t2, &l);
            sb++;
            tim[i].s = s1*60+s2;
            tim[i].e = t1*60+t2;
            tim[i].l = l;
        }
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i!=j){
                    if(tim[i].s<tim[j].s+tim[j].l && tim[j].s<tim[i].s+tim[i].l) add(i<<1, j<<1|1, edge1, head1, cnt1);
                    if(tim[i].s<tim[j].e && tim[j].e-tim[j].l<tim[i].s+tim[i].l) add(i<<1, j<<1, edge1, head1, cnt1);
                    if(tim[i].e-tim[i].l<tim[j].s+tim[j].l && tim[j].s<tim[i].e) add(i<<1|1, j<<1|1, edge1, head1, cnt1);
                    if(tim[i].e-tim[i].l<tim[j].e && tim[j].e-tim[j].l<tim[i].e) add(i<<1|1, j<<1, edge1, head1, cnt1);
                }
            }
        }
        for(int i = 0; i < n+n; i++){
            if(!dfn[i]) dfs(i);
        }
        for(int i = 0; i < n+n; i++){
            for(int j = head1[i]; j != -1; j = edge1[j].next){
                int v = edge1[j].v;
                if(sccno[i] != sccno[v]){
                    add(sccno[v], sccno[i], edge2, head2, cnt2);
                    in[sccno[i]]++;
                }
            }
        }
        bool flag = false;
        for(int i = 0; i < n; i++){
            if(sccno[i<<1]==sccno[i<<1|1]){
                flag = true;
                break;
            }
            ct[sccno[i<<1]] = sccno[i<<1|1];
            ct[sccno[i<<1|1]] = sccno[i<<1];
        }

        if(flag) puts("NO");
        else{
            toposort();
            for(int i = 0; i < n+n; i++){
                if(color[sccno[i]]==1) ans[i] = 1;
            }
            puts("YES");
            for(int i = 0; i < n; i++) {
                if(ans[i<<1]) printf("%02d:%02d %02d:%02d\n", tim[i].s/60, tim[i].s%60, (tim[i].s+tim[i].l)/60, (tim[i].s+tim[i].l)%60);
                else printf("%02d:%02d %02d:%02d\n", (tim[i].e-tim[i].l)/60, (tim[i].e-tim[i].l)%60, tim[i].e/60, tim[i].e%60);
            }
        }
    }
    return 0;
}
