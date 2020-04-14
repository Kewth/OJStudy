#if 0
2020.04.14

如果没有修改，可以用点分治简单统计这个路径信息。
带上修改就动态点分治，同时用堆动态维护信息。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cctype>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator char () { char s[5]; return scanf("%s", s), *s; }
} read;

const int maxn = 100005;
int st[20][maxn << 1], hb[maxn << 1], first[maxn], stp;
int deep[maxn];
std::vector<int> G[maxn];
bool ban[maxn];
int size[maxn], son[maxn];
int dfa[maxn], dsize[maxn];

void stinit () {
	for (int i = 2; i <= stp; i ++)
		hb[i] = hb[i >> 1] + 1;
	for (int i = stp; i; i --)
		for (int k = 1; i + (1 << k) - 1 <= stp; k ++)
			st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);
}

void dfs (int u, int f) {
	st[0][first[u] = ++ stp] = deep[u] = deep[f] + 1;
	for (int v : G[u])
		if (v != f) {
			dfs(v, u);
			st[0][++ stp] = deep[u];
		}
}

inline int dis (int x, int y) {
	int l = first[x], r = first[y];
	if (l > r) std::swap(l, r);
	int k = hb[r - l + 1];
	return deep[x] + deep[y] - std::min(st[k][l], st[k][r - (1 << k) + 1]) * 2;
}

void getsize (int u, int f) {
	size[u] = 1, son[u] = 0;
	for (int v : G[u])
		if (!ban[v] and v != f) {
			getsize(v, u);
			size[u] += size[v];
			if (size[v] > size[son[u]])
				son[u] = v;
		}
}

int divide (int s) {
	getsize(s, 0);
	int n = size[s], rt = s;
	while (size[son[rt]] * 2 > n)
		rt = son[rt];
	dsize[rt] = n;
	ban[rt] = 1;
	for (int u : G[rt])
		if (!ban[u]) {
			int v = divide(u);
			dfa[v] = rt;
		}

	return rt;
}

struct Heap {
	std::priority_queue<int> a, b;
	void insert (int x) { a.push(x); }
	void erase (int x) { b.push(x); }
	int max () {
		while (!b.empty() and a.top() == b.top())
			a.pop(), b.pop();
		return a.top();
	}
	int max_and_semax () {
		int tmp = max();
		a.pop();
		int res = max();
		a.push(tmp);
		return res + tmp;
	}
	int size () { return int(a.size() - b.size()); }
	Heap () { }
} hf[maxn], hg[maxn], ans;

int sta[maxn];
void vmodify (int u, int t) {
	for (int f = dfa[u], s = u; s; s = f, f = dfa[f]) {
		if (f and hf[f].size() >= 2) ans.erase(hf[f].max_and_semax());
		if (f and hg[s].size() >= 1) hf[f].erase(hg[s].max());
		if (t == 1) hg[s].insert(dis(f, u));
		if (t == -1) hg[s].erase(dis(f, u));
		if (f and hg[s].size() >= 1) hf[f].insert(hg[s].max());
		if (f and hf[f].size() >= 2) ans.insert(hf[f].max_and_semax());
	}
	sta[u] = t;
}

int main () {
	int n = read;
	for (int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs(1, 0);
	stinit();
	divide(1);

	for (int i = 1; i <= n; i ++) vmodify(i, 1);

	int q = read;
	while (q --) {
		char o = read;
		if (o == 'G') printf("%d\n", ans.max() ? ans.max() : -1);
		if (o == 'C') {
			int u = read;
			vmodify(u, - sta[u]);
		}
	}
}
