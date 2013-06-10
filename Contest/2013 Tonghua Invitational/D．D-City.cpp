/********************************
给一个图，问从编号为1的边开始每删除一条边剩多少个连通块，倒着做并查集即可。
*********************************/
#include <stdio.h>
#include <string.h>
#include <stack>

const int maxn = 10011;
const int maxm = 100011;
struct node{
    int u;
    int v;
}edge[maxm];
int father[maxn];
int n, m;

void init(){
    for(int i = 0; i <= n; i++){
        father[i] = i;
    }
}

int findx(int x){
    if(x != father[x]) father[x] = findx(father[x]);
    return father[x];
}

int merge(int x, int y){
    int fx = findx(x);
    int fy = findx(y);
    if(fx < fy){
        father[fx] = fy;
        n--;
    }
    else if(fy < fx){
        father[fy] = fx;
        n--;
    }
}

int main(){
    while(~scanf("%d %d", &n, &m)){
        init();
        std::stack<int>st;
        for(int i = 0; i < m; i++){
            scanf("%d %d", &edge[i].u, &edge[i].v);
        }
        st.push(n);
        for(int i = m-1; i > 0; i--){
            int u = edge[i].u;
            int v = edge[i].v;
            merge(u, v);
            st.push(n);
        }
        while(!st.empty()){
            printf("%d\n", st.top());
            st.pop();
        }
    }
    return 0;
}
