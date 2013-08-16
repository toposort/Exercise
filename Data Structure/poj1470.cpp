#include <stdio.h>
#include <string.h>

const int maxn = 1005;
const int maxm = 500011;
bool viss[maxn];
int res[maxn];
int n, m;
struct Gragh{
    struct Gragh_Node{
        int u, v;
        int opp;
        int next;
        int res;
    }arc[maxm];
    int cnt, head[maxn];
    void init(){
        cnt = 0;
        memset(head, -1, sizeof(int)*(n+1));
    }
    void d_insert(int u, int v){
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].res = 0;
        arc[cnt].next = head[u];
        head[u] = cnt++;
    }
    void u_insert(int u, int v){
        arc[cnt].u = u;
        arc[cnt].v = v;
        arc[cnt].res = 0;
        arc[cnt].next = head[u];
        arc[cnt].opp = cnt+1;
        head[u] = cnt++;
        arc[cnt].u = v;
        arc[cnt].v = u;
        arc[cnt].res = 0;
        arc[cnt].next = head[v];
        arc[cnt].opp = cnt-1;
        head[v] = cnt++;
    }
    ~Gragh(){
        delete[]arc;
        delete[]head;

    }
};
struct Disjoint_Sets{
    struct Sets{
        int father;
        int ranks;
    }S[maxn];
    void Init(int n){
        for(int i = 0; i <= n; i++){
            S[i].father = i;
            S[i].ranks = 0;
        }
    }
    int Father(int x){
        if(S[x].father == x) return x;
        S[x].father = Father(S[x].father);
        return S[x].father;
    }
    bool Union(int x, int y){
        int fx = Father(x), fy = Father(y);
        if(fx == fy) return false;
        if(S[fx].ranks > S[fy].ranks) S[fy].father = fx;
        else{
            S[fx].father = fy;
            if(S[fx].ranks == S[fy].ranks){
                ++S[fy].ranks;
            }
        }
        return true;
    }
    ~Disjoint_Sets(){
        delete []S;
    }
};
struct LCA{
    Gragh G, Q;
    Disjoint_Sets DS;
    int ancestor[maxn];
    int indegree[maxn];
    bool vis[maxn];
    void init(int n){
        memset(ancestor, 0, sizeof(int)*(n+1));
        memset(vis, 0, sizeof(bool)*(n+1));
        G.init();
        Q.init();
        DS.Init(n);
    }
    void insert_gragh(int u, int v){
        G.d_insert(u, v);
    }
    void insert_query(int u, int v){
        Q.u_insert(u, v);
    }
    void lca(int u){
        ancestor[u] = u;
        for(int i = G.head[u]; i != -1; i = G.arc[i].next){
            int v = G.arc[i].v;
            lca(v);
            DS.Union(u, v);
            ancestor[DS.Father(u)] = u;
        }
        vis[u] = 1;
        for(int i = Q.head[u]; i != -1; i = Q.arc[i].next){
            int v = Q.arc[i].v;
            if(vis[v]) Q.arc[i].res = ancestor[DS.Father(v)];
            Q.arc[Q.arc[i].opp].res = ancestor[DS.Father(v)];
        }
    }
    void solve(int n){
        memset(vis, 0, sizeof(bool)*(n+1));
        memset(indegree, 0, sizeof(int)*(n+1));
        for(int i = 0; i < G.cnt; i++){
            ++indegree[G.arc[i].v];
        }
        for(int i = 1; i <= n; i++){
            if(indegree[i]==0) lca(i);
        }
    }
    ~LCA(){
        delete []vis;
        delete []indegree;
        delete []ancestor;
    }
}L;

int main(){
    while(~scanf("%d", &n)){
        char str[111];
        L.init(n);
        memset(res, 0, sizeof(int)*(n+1));
        memset(viss, false, sizeof(bool)*(n+1));
        for(int i = 0; i < n; i++){
            int u, v, m;
            scanf("%d", &u);
            scanf("%[^0-9]", str);
            scanf("%d", &m);
            scanf("%[^0-9]", str);
            for(int j = 0; j < m; j++){
                scanf("%d", &v);
                L.insert_gragh(u, v);
                viss[v] = true;
            }
        }
        scanf("%d", &m);
        for(int i =0; i < m; i++){
            int u, v;
            scanf("%[^0-9]", str);
            scanf("%d", &u);
            scanf("%[^0-9]", str);
            scanf("%d", &v);
            L.insert_query(u, v);
        }
        L.solve(n);
        for(int i = 1; i <= m; i++){
            ++res[L.Q.arc[2*i-1].res];
        }
        for(int i = 1; i <= n; i++){
            if(res[i]) printf("%d:%d\n", i, res[i]);
        }
        scanf("%[^0-9]", str);
    }
    return 0;
}

