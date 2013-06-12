/************************************************
给定一个图，所有的顶点都可以赋一个值ａ，判断是不是满足可以找到一个数Ｔ，满足：
(a) |ai| < T for all i and
(b) (vi, vj) in E <=> |ai - aj| >= T。
由(vi, vj) in E => |ai - aj| >= T 可以得出：
原图必须为一个二分图，这样一正一负就可以满足条件。
由(vi, vj) in E <= |ai - aj| >= T 可以得出：
原图包含边的连通分量个数必须只有一个。
那么tarjan求一下包含边的连通分量个数，然后判定下是否二分图即可。
*************************************************/

#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stack>

const int maxn = 311;
const int maxm = maxn*maxn;
struct node{
    int u;
    int v;
    int next;
}edge[maxm];
int head[maxn], color[maxn], dfn[maxn], low[maxn], sccno[maxn];
int ss, n, cnt, dfs_clock, scc_cnt, numm;
std::stack<int>st;

void init(){
    ss = 0;
    cnt = 0;
    numm = 0;
    scc_cnt = 0;
    dfs_clock = 0;
    for(int i = 0; i <= n; i++){
        head[i] = -1;
        color[i] = 0;
        sccno[i] = 0;
        dfn[i] = 0;
        low[i] = 0;
    }
}

void add(int u, int v){
    edge[cnt].u = u;
    edge[cnt].v = v;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}

bool check(int u){
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].v;
        if(color[u] == color[v]) return false;
        if(!color[v]){
            color[v] = 3-color[u];
            if(!check(v)) return false;
        }
    }
    return true;
}

void dfs(int u){
    low[u] = dfn[u] = ++dfs_clock;
    st.push(u);
    for(int i = head[u]; i != -1; i = edge[i].next){
        int v = edge[i].v;
        if(!dfn[v]){
            dfs(v);
            low[u] = std::min(low[u], low[v]);
        }
        else if(!sccno[v]){
            low[u] = std::min(low[u], dfn[v]);
        }
    }
    if(low[u] == dfn[u]){
        ++scc_cnt;
        int tot = 0;
        while(1){
            int x = st.top();
            st.pop();
            sccno[x] = scc_cnt;
            ++tot;
            if(x==u) break;
        }
        if(tot>1){
            ss = u;
            ++numm;
        }
    }
}

int main(){
    int t;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        init();
        for(int i = 0; i < n; i++){
            std::string s;
            std::cin>>s;
            for(int j = 0; j < n; j++){
                if(s[j]=='1') add(i, j);
            }
        }
        for(int i = 0; i < n; i++){
            if(!dfn[i]) dfs(i);
        }
        if(numm<=1){
            color[ss] = 1;
            if(check(ss)){
                puts("Yes");
                continue;
            }
        }
        puts("No");
    }
    return 0;
}
