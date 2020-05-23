#if 0
2020.05.23

  可以发现对于一个点数大于 1 的边双联通分量，只要进入就可以遍历联通分量的所有点并从任
意位置出来。边双缩点，在边双树上称大小超过 1 的点为黑点。
  进一步观察可以发现，对于两个黑点路径上的任意一个点，它具有和黑点同样的性质，只要进入
该点，就可以通过两个黑点以任意位置出来，因此不妨将黑点之间的点也染黑。
  更进一步，源点所在联通分量也有类似的性质，不妨将源点所在分量设为根并染黑，这样其他点
的染色会方便很多。
  这样一来，黑点形成了一个联通块，可以遍历所有黑点，然后选择一个白点作为终点，选择贡献
最大的白点即可。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 200005;
std::vector<int> G[maxn], T[maxn];
ll nval[maxn];
int val[maxn];
bool ntyp[maxn];

int dfn[maxn], low[maxn], belong[maxn], ip, bp;
int stack[maxn], sp;
std::vector<int> con[maxn];
void dfs(int u, int from) {
	low[u] = dfn[u] = ++ ip;
	stack[++ sp] = u;
	for(int v : G[u]) {
		if(!dfn[v]) {
			dfs(v, u);
			low[u] = std::min(low[u], low[v]);
		} else if(dfn[v] < dfn[u] and v != from)
			low[u] = std::min(low[u], dfn[v]);
	}
	if(low[u] == dfn[u]) {
		++ bp;
		while(stack[sp + 1] != u) {
			int x = stack[sp --];
			belong[x] = bp;
			con[bp].push_back(x);
		}
	}
}

bool vis[maxn];
void rebuild() {
	for(int u = 1; u <= bp; u ++) {
		vis[u] = 1;
		for(int x : con[u])
			for(int v : G[x])
				if(!vis[belong[v]]) {
					T[u].push_back(belong[v]);
					vis[belong[v]] = 1;
				}
		for(int x : con[u])
			for(int v : G[x])
				vis[belong[v]] = 0;
		vis[u] = 0;
	}
}

int fa[maxn], deep[maxn];
void dfs (int u) {
	deep[u] = deep[fa[u]] + 1;
	for (int v : T[u])
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
		}
}

ll sum = 0, max = 0;
void calc (int u, ll now) {
	if (!ntyp[u]) now += nval[u];
	else sum += nval[u];
	max = std::max(max, now);
	for (int v : T[u])
		if (v != fa[u])
			calc(v, now);
}

int main () {
	int n = read, m = read;
	for (int i = 1; i <= n; i ++) read(val[i]);
	for (int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	for (int i = 1; i <= n; i ++)
		if (!dfn[i])
			dfs(i, 0);
	rebuild();

	int S = read, R = belong[S];
	ntyp[R] = 1;
	dfs(R);

	for (int u = 1; u <= bp; u ++) {
		if (con[u].size() > 1) ntyp[u] = 1;
		for (int x : con[u])
			nval[u] += val[x];
		if (ntyp[u])
			for (int x = fa[u]; x and !ntyp[x]; x = fa[x])
				ntyp[x] = 1;
	}

	calc(R, 0);
	printf("%lld\n", sum + max);
}
