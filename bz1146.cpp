#if 0
2019.12.25

练练数据结构，耗时 40min+ 。
树上待修区间第 k 大，树剖转链，然后树状数组套动态开点线段树，时间放的比较松，不需要离散化。
#endif
#include <cstdio>
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

const int maxn = 80005, maxv = 100000005;
struct Tree {
	int val;
	int lti, rti;
};
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
Tree pool[maxn * 400];
int tp;
int tree[maxn];

void add(int &now, int L, int R, int p, int x) {
	if(!now) now = ++ tp;
	/* if(tp % maxn == 0) debug("%d\n", tp); */
	self.val += x;
	if(L == R) return;
	int M = (L + R) >> 1;
	if(p <= M) add(self.lti, L, M, p, x);
	else add(self.rti, M + 1, R, p, x);
}

std::vector<int> ktr, ktl;
int kth(int k, int L, int R) {
	if(L == R) return L;
	int sz = 0;
	int M = (L + R) >> 1;
	for(int now : ktr) sz += rt.val;
	for(int now : ktl) sz -= rt.val;
	/* debug("%d in %d-%d(%d)\n", k, L, R, sz); */
	if(k <= sz) {
		for(int &now : ktr) now = self.rti;
		for(int &now : ktl) now = self.rti;
		return kth(k, M + 1, R);
	}
	else {
		for(int &now : ktr) now = self.lti;
		for(int &now : ktl) now = self.lti;
		return kth(k - sz, L, M);
	}
}

std::vector<int> G[maxn];
int top[maxn], deep[maxn], son[maxn], size[maxn], fa[maxn];
int id[maxn], ip;

void dfs1(int u) {
	deep[u] = deep[fa[u]] + 1;
	size[u] = 1;
	for(int v : G[u])
		if(v != fa[u]) {
			fa[v] = u;
			dfs1(v);
			size[u] += size[v];
			if(size[v] > size[son[u]])
				son[u] = v;
		}
}

int dv[maxn];
int n;
void dfs2(int u) {
	id[u] = ++ ip;
	for(int k = ip; k <= n; k += k & -k)
		add(tree[k], 1, maxv, dv[u], 1);
	if(!top[u]) top[u] = u;
	if(son[u]) {
		top[son[u]] = top[u];
		dfs2(son[u]);
		for(int v : G[u])
			if(v != fa[u] and v != son[u])
				dfs2(v);
	}
}

int prekth(int x, int y, int K) {
	int lp = 0, rp = 0;
	ktr.clear();
	ktl.clear();

	while(top[x] != top[y]) {
		if(deep[top[x]] < deep[top[y]]) std::swap(x, y);
		for(int k = id[x]; k; k -= k & -k)
			ktr.push_back(tree[k]);
		for(int k = id[top[x]] - 1; k; k -= k & -k)
			ktl.push_back(tree[k]);
		/* debug("%d -> %d\n", x, top[x]); */
		x = fa[top[x]];
	}

	if(deep[x] < deep[y]) std::swap(x, y);
	for(int k = id[x]; k; k -= k & -k)
		ktr.push_back(tree[k]);
	for(int k = id[y] - 1; k; k -= k & -k)
		ktl.push_back(tree[k]);
	/* debug("%d -> %d\n", x, y); */

	int sz = 0;
	for(int now : ktr) sz += self.val;
	for(int now : ktl) sz -= self.val;
	if(K <= sz) return kth(K, 1, maxv);
	return -1;
}

int main() {
	read(n);
	int q = read;

	for(int i = 1; i <= n; i ++)
		read(dv[i]);
	for(int i = 1; i < n; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	dfs1(1);
	dfs2(1);

	while(q --) {
		int K = read, x = read, y = read;
		if(!K) {
			for(int k = id[x]; k <= n; k += k & -k)
				add(tree[k], 1, maxv, dv[x], -1);
			dv[x] = y;
			for(int k = id[x]; k <= n; k += k & -k)
				add(tree[k], 1, maxv, dv[x], 1);
		} else {
			int ans = prekth(x, y, K);
			if(ans == -1) puts("invalid request!");
			else printf("%d\n", ans);
		}
	}
}
