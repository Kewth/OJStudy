#if 0
2020.05.13

  考虑求出每个子树的 SG 值。对于子树根节点 u ，首先一个可行的操作是删掉 u 本身，这样可以
转移到 sg[v1] ^ sg[v2] ^ ... ，如果操作的点不是 u 本身，假设操作在 u 的儿子 v1 的子树内，
那么就会转移到 k ^ sg[v2] ^ ... ，其中 k 是 v1 子树内可以转移到的任意一个状态。
  那么用 01 Tire 维护每个子树能转移到的局面，u 节点的 Trie 就是儿子的 Trie 异或一个值后
合并的结果。求出 u 子树的 SG 值只需要在 Trie 树上二分找到 mex 。
  一个小 trick: 树要以编号最小的点为根，按编号顺序枚举的时候碰到一个点可以直接作为根。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxk = 20;
std::vector<int> G[maxn];
bool vis[maxn];
int sg[maxn];
struct Trie {
	int lti, rti, tag, full;
} pool[maxn * (maxk + 1)];
int pp;
#define self pool[now]
#define lt pool[self.lti]
#define rt pool[self.rti]
int tr[maxn];

inline void push (int now, int k) {
	if (!self.tag) return;
	if (self.tag >> k & 1) {
		std::swap(self.lti, self.rti);
	}
	if (self.lti) lt.tag ^= self.tag;
	if (self.rti) rt.tag ^= self.tag;
	self.tag = 0;
}

void merge (int &now, int an, int k) {
	if (!now or pool[an].full) return now = an, void();
	if (!an or self.full) return;
	push(now, k);
	push(an, k);
	merge(self.lti, pool[an].lti, k - 1);
	merge(self.rti, pool[an].rti, k - 1);
	self.full = lt.full and rt.full;
}

inline int newlain (int x) {
	int las = ++ pp;
	pool[las].full = 1;
	for (int k = 0; k < maxk; k ++) {
		int now = ++ pp;
		self = {0, 0, 0, 0};
		if (x >> k & 1) self.rti = las;
		else self.lti = las;
		las = now;
	}
	return las;
}

int find (int now) {
	int res = 0;
	for (int k = maxk - 1; now and k >= 0; k --) {
		push(now, k);
		if (!lt.full) now = self.lti;
		else now = self.rti, res ^= 1 << k;
	}
	return res;
}

void game (int u, int fa) {
	vis[u] = 1;
	int Sg = 0;
	for (int v : G[u])
		if (v != fa) {
			game(v, u);
			Sg ^= sg[v];
		}

	tr[u] = newlain(Sg);

	for (int v : G[u])
		if (v != fa) {
			pool[tr[v]].tag ^= Sg ^ sg[v];
			merge(tr[u], tr[v], maxk - 1);
		}

	sg[u] = find(tr[u]);
	/* debug("%d : %d\n", u, sg[u]); */
}

int main () {
	int T = read;
	while (T --) {
		int n = read, m = read;
		std::fill(vis, vis + n + 1, 0);
		std::fill(G, G + n + 1, std::vector<int>());
		pp = 0;

		for (int i = 1; i <= m; i ++) {
			int u = read, v = read;
			G[u].push_back(v);
			G[v].push_back(u);
		}

		int Sg = 0;
		for (int i = 1; i <= n; i ++)
			if (!vis[i]) {
				game(i, 0);
				Sg ^= sg[i];
			}

		if (Sg) puts("Alice");
		else puts("Bob");

#ifdef LOCAL
		printf("%d\n", Sg);
#endif
	}
}
