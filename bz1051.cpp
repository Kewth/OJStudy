#if 0
2020.01.09

强连通分量缩点，DAG 上如果存在唯一的没有出度的点，则该点能被所有点到达。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 10005;
std::vector<int> G[maxn], D[maxn], con[maxn];
bool ins[maxn];
int stack[maxn], sp;
int dfn[maxn], low[maxn], ip;
int belong[maxn], bp;

void dfs(int u) {
	low[u] = dfn[u] = ++ ip;
	stack[++ sp] = u;
	ins[u] = 1;
	for(int v : G[u])
		if(!dfn[v]) {
			dfs(v);
			low[u] = std::min(low[u], low[v]);
		} else if(ins[v])
			low[u] = std::min(low[u], low[v]);
	if(low[u] == dfn[u]) {
		++ bp;
		while(stack[sp + 1] != u) {
			int x = stack[sp --];
			ins[x] = 0;
			belong[x] = bp;
			con[bp].push_back(x);
		}
		for(int x : con[bp])
			for(int v : G[x])
				if(belong[v] != bp)
					D[bp].push_back(v);
	}
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
	}

	for(int i = 1; i <= n; i ++)
		if(!dfn[i])
			dfs(i);

	std::vector<int> ans;
	for(int b = 1; b <= bp; b ++)
		if(D[b].empty())
			ans.push_back(b);

	if(ans.size() == 1)
		printf("%lu\n", con[ans.back()].size());
	else
		puts("0");
}
