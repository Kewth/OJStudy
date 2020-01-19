#if 0
2020.01.17

线性消元板子。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
std::vector<par> G[maxn];

int f[maxn], g[maxn];
int root, tot;
void dfs(int u, int from) {
	for(par p : G[u]) {
		int v = p.first;
		if(v != from and tot < 2) {
			if(v == root) {
				if(++ tot == 2) return;
				f[v] = 0;
				g[v] = (p.second - g[u]) >> 1;
			} else {
				f[v] = - f[u];
				g[v] = p.second - g[u];
			}
			dfs(v, u);
		}
	}
}

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++) {
		int a = read, b = read, c = read;
		G[a].push_back(par(b, c));
		G[b].push_back(par(a, c));
	}

	root = 1;
	f[1] = 1;
	dfs(1, 0);

	for(int i = 1; i <= n; i ++)
		printf("%d\n", g[i]);
}
