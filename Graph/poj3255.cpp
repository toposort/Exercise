#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const int K = 2;
const int maxn = 5011;
const int maxm = 200011;
class states{
public:
	int cost,id;
};
int dist[maxn], num[maxn];;
class cmp{
public:
	bool operator ()(const states &i,const states &j){
		return i.cost>j.cost;
	}
};
class cmp2{
public:
	bool operator ()(const states &i,const states &j){
		return i.cost+dist[i.id]>j.cost+dist[j.id];
	}
};
struct edges{
	int to,next,cost;
}edger[maxm], edge[maxm];
int headr[maxn], head[maxn], Lr, L;

void dijkstra(int s){
	states u;
	u.id = s;
	u.cost = 0;
	dist[s] = 0;
	priority_queue<states, vector<states>, cmp> q;
	q.push(u);
	while(!q.empty()){
		u = q.top();
		q.pop();
		if(u.cost != dist[u.id]) continue;
		for(int i = headr[u.id]; i != -1; i = edger[i].next){
			states v = u;
			v.id = edger[i].to;
			if(dist[v.id] > dist[u.id]+edger[i].cost){
				v.cost = dist[v.id] = dist[u.id]+edger[i].cost;
				q.push(v);
			}
		}
	}
}

void init(int n){
	Lr=L=0;
	memset(head, -1, 4*n);
	memset(headr, -1, 4*n);
	memset(dist, 63, 4*n);
	memset(num, 0, 4*n);
}

void add_edge(int u, int v, int x){
	edge[L].to = v;
	edge[L].cost = x;
	edge[L].next = head[u];
	head[u] = L++;
	edger[Lr].to = u;
	edger[Lr].cost = x;
	edger[Lr].next = headr[v];
	headr[v] = Lr++;
}

int a_star(int s, int t){
	if(dist[s]==0x3f3f3f3f) return -1;
	priority_queue<states, vector<states>, cmp2> q;
	states tmp;
	tmp.id = s;
	tmp.cost = 0;
	q.push(tmp);
	while(!q.empty()){
		states u = q.top();
		q.pop();
		num[u.id]++;
		if(num[t]==K) return u.cost;
		for(int i = head[u.id]; i != -1; i = edge[i].next){
			int v = edge[i].to;
			tmp.id = v;
			tmp.cost = u.cost+edge[i].cost;
			q.push(tmp);
		}
	}
	return -1;
}
int main(){
	int n, m;
	scanf("%d %d", &n, &m);
	init(n);
	for(int i = 0; i < m; i++){
		int u, v, x;
		scanf("%d %d %d", &u, &v, &x);
		add_edge(u-1, v-1, x);
		add_edge(v-1, u-1, x);
	}
	dijkstra(n-1);
	printf("%d\n", a_star(0, n-1));
	return 0;
}
