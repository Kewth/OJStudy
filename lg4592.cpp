#if 0
2020.04.28

  对于第一个询问，对于 dfs 序建可持久化 01 Trie 即可。
  对于第二个询问，容易想到在上述做法的基础上套用树剖，但事实上可以维护每个点到根的可持久化
01 Trie ，这样对于一条链可以拆成两个区间进行查询。
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

const int maxn = 100005, maxk = 30;
int st[20][maxn << 1], hb[maxn << 1], first[maxn], stp;
int id[maxn], iid[maxn], fa[maxn], ip;
int size[maxn];
int val[maxn];
int tr1[maxn], tr2[maxn];
int ch[maxn * (maxk + 1) * 2][2], sum[maxn * (maxk + 1) * 2], cp;
std::vector<int> G[maxn];

void stinit () {
	for (int i = 2; i <= stp; i ++)
		hb[i] = hb[i >> 1] + 1;
	for (int i = stp; i; i --)
		for (int k = 1; i + (1 << k) - 1 <= stp; k ++)
			st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);
}

void dfs (int u) {
	iid[id[u] = ++ ip] = u;
	st[0][first[u] = ++ stp] = id[u];
	size[u] = 1;
	for (int v : G[u])
		if (v != fa[u]) {
			fa[v] = u;
			dfs(v);
			size[u] += size[v];
			st[0][++ stp] = id[u];
		}
}

inline int lca (int x, int y) {
	int l = first[x], r = first[y];
	if (l > r) std::swap(l, r);
	int k = hb[r - l + 1];
	return iid[std::min(st[k][l], st[k][r - (1 << k) + 1])];
}

int lain (int an, int x, int k) {
	int now = ++ cp;
	ch[now][0] = ch[an][0];
	ch[now][1] = ch[an][1];
	sum[now] = sum[an] + 1;
	if (k >= 0) {
		int t = x >> k & 1;
		ch[now][t] = lain(ch[now][t], x, k - 1);
	}
	return now;
}

int query (int a, int b, int x, int k) {
	if (k == -1) return 0;
	int t = x >> k & 1;
	if (sum[ch[a][!t]] > sum[ch[b][!t]])
		return 1 << k | query(ch[a][!t], ch[b][!t], x, k - 1);
	return query(ch[a][t], ch[b][t], x, k - 1);
}

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++) read(val[i]);
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1);
	stinit();

	for (int i = 1; i <= ip; i ++) {
		int u = iid[i];
		tr1[i] = lain(tr1[i - 1], val[u], maxk - 1);
		tr2[u] = lain(tr2[fa[u]], val[u], maxk - 1);
	}

	while (q --) {
		int o = read;
		if (o == 1) {
			int u = read, x = read;
			printf("%d\n", query(tr1[id[u] + size[u] - 1], tr1[id[u] - 1], x, maxk - 1));
		}
		if (o == 2) {
			int u = read, v = read, x = read;
			int c = lca(u, v);
			printf("%d\n", std::max(query(tr2[u], tr2[fa[c]], x, maxk - 1),
						query(tr2[v], tr2[fa[c]], x, maxk - 1)));
		}
	}
}
