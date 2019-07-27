#if 0
2019.07.27

经典树分块方式。
dfs ，每个节点需保证分好一些块后剩下的点最多 b 个，包括 u ，构成联通块。
那么 dfs 的时候把儿子的剩下的点逐渐加进自己的集合，一到 b 就分一个块，大小最多 2b - 1 。
最后把根节点的剩余集合分到最后一个块里头，大小最多 3b - 1 。
#endif
#include <cstdio>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1010;
int a[maxn], color[maxn], top[maxn], cp;
std::vector<int> G[maxn], B[maxn];

void add(int u) {
	// debug("add %d\n", u);
	// for(int d : B[u])
		// debug(" %d", d);
	// debug("\n");
	cp ++;
	for(int d : B[u])
		color[d] = cp;
	B[u].clear();
	top[cp] = u;
}

void dfs(int u, int fa, int b) {
	for(int v : G[u])
		if(v != fa) {
			dfs(v, u, b);
			for(int d : B[v])
				B[u].push_back(d);
			if(B[u].size() >= b)
				add(u);
		}
	B[u].push_back(u);
}

int main() {
	int n = input(), b = input();
	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		G[u].push_back(v);
		G[v].push_back(u);
	}
	dfs(1, 0, b);
	for(int d : B[1])
		color[d] = cp;
	printf("%d\n", cp);
	for(int u = 1; u <= n; u ++)
		printf("%d ", color[u]);
	puts("");
	for(int i = 1; i <= cp; i ++)
		printf("%d ", top[i]);
	puts("");
}
