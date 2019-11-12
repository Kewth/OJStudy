#if 0
2019.11.12

有环缩点，无环 DP 。
假设图为 DAG ， DP 设 f[u] 表示到 u 的路径最大极值，
max[u], min[u] 表示到 u 的路径最大值和最小值，用于辅助转移，
那么从 u 到 v 的转移只需考虑 u -> v 这条边是作为最大值还是最小值还是中间值即可。
无向图缩点后也是类似的，把强连通分量的边全走一遍一定不会更劣，
每个强连通分量记 firmin, firmax 表示强连同分量内部的边权最小值和最大值，
用这两个值自己转移自己即可。
#endif
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 500005, inf = 1000000001;
/* int head[maxn], nxt[maxn], to[maxn], val[maxn], hp; */
int f[maxn], min[maxn], max[maxn];
int firmin[maxn], firmax[maxn];
std::vector<Par> G[maxn], D[maxn];

int stack[maxn], sp;
bool ins[maxn];
int dfn[maxn], low[maxn], ip;
int belong[maxn], bp;
std::vector<int> contain[maxn];
int deg[maxn];

void dfs(int u) {
	low[u] = dfn[u] = ++ ip;
	stack[++ sp] = u;
	ins[u] = 1;

	for(Par p : G[u])
		if(!dfn[p.first]) {
			dfs(p.first);
			low[u] = std::min(low[u], low[p.first]);
		} else if(ins[p.first])
			low[u] = std::min(low[u], low[p.first]);

	if(low[u] == dfn[u]) {
		++ bp;
		while(stack[sp + 1] != u) {
			int x = stack[sp --];
			ins[x] = 0;
			contain[bp].push_back(x);
			belong[x] = bp;
			debug("%d in %d\n", x, bp);
		}

		min[bp] = firmin[bp] = 1000000000;
		max[bp] = firmax[bp] = 0;
		for(int x : contain[bp])
			for(Par p : G[x]) {
				int v = belong[p.first];
				if(v == bp) {
					firmin[bp] = std::min(firmin[bp], p.second);
					firmax[bp] = std::max(firmax[bp], p.second);
					debug(" in (%d)\n", p.second);
				}
				else {
					debug(" %d -> %d (%d)\n", bp, v, p.second);
					D[bp].push_back(Par(v, p.second));
					deg[v] ++;
				}
			}
		f[bp] = firmax[bp] - firmin[bp];
	}
}

bool ok[maxn];
int main() {
	read.operator int();
	int m = read, q = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read, w = read;
		G[u].push_back(Par(v, w));
	}

	dfs(1);

	std::queue<int> qu;
	for(int i = 1; i <= bp; i ++)
		if(!deg[i])
			qu.push(i);

	ok[belong[1]] = 1;

	while(!qu.empty()) {
		int u = qu.front();
		qu.pop();

		if(ok[u]) {
			debug("%d: %d %d %d %d %d\n", u, f[u], min[u], max[u], firmin[u], firmax[u]);
			f[u] = std::max({f[u], max[u] - firmin[u], firmax[u] - min[u]});
			min[u] = std::min(min[u], firmin[u]);
			max[u] = std::max(max[u], firmax[u]);
			debug("%d: %d %d %d\n", u, f[u], min[u], max[u]);
		}

		for(Par p : D[u]) {
			int v = p.first, w = p.second;
			if(ok[u]) {
				f[v] = std::max({0, f[v], f[u], max[u] - w, w - min[u]});
				min[v] = std::min({min[v], min[u], w});
				max[v] = std::max({max[v], max[u], w});
				ok[v] = 1;
			}
			if(-- deg[v] == 0)
				qu.push(v);
		}
	}

	while(q --) {
		int u = belong[read];
		if(!ok[u] or f[u] < 0)
			puts("-1");
		else
			printf("%d\n", f[u]);
	}
}
