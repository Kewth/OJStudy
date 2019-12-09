#if 0
2019.12.08

题目相当于给每个点一个 label ，满足对于任意 label = k 的两个点 (u, v) ，
满足在路径 u-v 上一定存在一个点 p 的 label > k 。
而目标则是最小化最大的 label 。

题目还对应于求最大深度最小的点分树，
那么最优解中每个点的 label 实际上就是该点在最优点分树上的子树最大深度。

考虑从叶子到根逐个贪心确定每个点 u 的最小 label[u] 。
同时记录 ban[u] 表示 u 子树内有哪些 label 还未被匹配，
k 在 u 子树内匹配当且仅当在每个 label = k 的点到 u 之间都已经有了 label > k 的点。
由于 label 的大小是 O(logn) 级别的，可以状压到一个数。

那么对于 u 的每个儿子 v ，将 ban[v] 按位或起来得到 x ，
一个 naive 的想法是 label[u] = （ x 第一个 0 的位置）。
但事实上，对于两个儿子 v1, v2 如果 ban[v1] & ban[v2] 不为零，
就意味着存在 k 使得两个子树内都需要匹配 k ，这要求 label[u] > k 。
那么将 ban[v1] & ban[v2] 的按位或计为 t ，
label[u] 需要满足在 x 上对应的位置为 0 ，且在 t 上对应的位置的是前导 0 。
官方给出的做法是 O(logn) 暴力枚举 label[u] 找出最小的合法值，
但事实上通过 __builtin 函数的位运算可以通过 x, t 来 O(1) 计算 label[u] 。

总复杂度 O(n) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int label[maxn], ban[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs(int u, int fa) {
	int t = 0;
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa) {
			dfs(to[i], u);
			t |= ban[u] & ban[to[i]];
			ban[u] |= ban[to[i]];
		}

	int k = t ? 32 - __builtin_clz(unsigned(t)) : 0;
	label[u] = __builtin_ctz(unsigned((ban[u] | ((1 << k) - 1)) + 1));
	ban[u] = (ban[u] >> label[u] | 1) << label[u];
	/* debug("%d : %d %d (%d)\n", u, label[u], ban[u], t); */
}

int main() {
	int n = read;

	for(int i = 1; i < n; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}

	dfs(1, 0);

	int ans = 0;
	for(int i = 1; i <= n; i ++)
		ans = std::max(ans, label[i]);
	printf("%d\n", ans);
}
