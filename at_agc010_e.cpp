#if 0
2019.08.08

两个不互质的数的左右关系被第一次操作安排后就不会因第二次操作再改变了。
考虑将不互质的数连无向边，那么第一次操作实际上就是给所有边定向，且不能成环，
之后就是 DAG ，第二次操作就是求一个拓扑序。

考虑两次操作分别如何做到最优。
先考虑第二次操作，显然就是求最大拓扑序，每次在入度为 0 的点中选值最大的放前头即可。
再考虑第一次操作，要求定向后第二次操作的结果字典序最小。
不同联通快之间只受第二次操作支配，那么只考虑每个联通块如何安排。
首先选最小值作为 DAG 的唯一根，第二次操作中它一定在联通块中最先被选，删掉它，
第二次操作中一定会第二选与它相连的点，为了让第二个选的尽量小，把根连接的点中的边从小向大连，
以此类推，具体地，用 dfs 实现，每次当前节点向连接的点中从小到大贪心定向即可。
#endif
#include <cstdio>
#include <algorithm>
#include <queue>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 2020;
int du[maxn];
int a[maxn];
bool link[maxn][maxn];
bool vis[maxn];
std::vector<int> G[maxn];

void dfs(int u, int n) {
	vis[u] = true;
	for(int v = 1; v <= n; v ++)
		if(not vis[v] and link[u][v] and u != v) {
			link[u][v] = link[v][u] = false;
			// debug("%d -> %d\n", u, v);
			G[u].push_back(v);
			du[v] ++;
			dfs(v, n);
		}
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	std::sort(a + 1, a + n + 1);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			if(std::__gcd(a[i], a[j]) > 1)
				link[i][j] = true;
	for(int i = 1; i <= n; i ++)
		if(not vis[i])
			dfs(i, n);
	std::priority_queue<Par> q;
	for(int i = 1; i <= n; i ++)
		q.push(Par(- du[i], i));
	while(not q.empty()) {
		int d = - q.top().first, u = q.top().second;
		q.pop();
		if(d != du[u]) continue;
		for(int v : G[u]) {
			du[v] --;
			q.push(Par(- du[v], v));
		}
		printf("%d ", a[u]);
	}
	puts("");
}
