#if 0
2020.04.07

去年 HNOI 居然有我能自己做的题！

首先不难发现没有操作当且仅当所有线段都形如 (i, n) 。
把线段看作点建图，从 (1, n) 所在的三角形开始，在一个三角形内，由一个点向另外两个点连边。
在这样建出来的有根二叉树上考虑问题，
事实上这个二叉树从根开始的右链是类似于虚节点一样的东西，仅用于保持树的形态。
那么只要从根向下对实际节点进行旋转操作就一定能把线段放在正确位置。
所以最小的操作次数就是实际节点的数量，而操作的方案数就是实际节点的拓扑序种类数。

树的拓扑序数量是 n! / mul(size[u]) ，每次操作 size 发生改变的点至多只有一个，很好维护。

ps:
对于建树，可以这么考虑：这个问题是可以分治处理的，如果分治处理问题，
那么上文所谓的二叉树实际上就是这个分治结构构成的二叉树。
而建树的目的就是为了能够支持修改而动态调整分治结构，否则就可以直接分治。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005, mod = 1000000007;
std::set<int> S[maxn];
std::map<par, int> map;
int np;
int ls[maxn], rs[maxn];
int fs[maxn];
int a[maxn];

inline ll power (ll x, int k) {
	if (k < 0) k += mod - 1;
	ll res = 1;
	while (k) {
		if (k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int n;
int build (int l, int r) {
	if (r == l + 1) return 0;
	int u = map[par(l, r)] = ++ np;
	int x = *S[r].upper_bound(l);
	ls[u] = build(l, x);
	rs[u] = build(x, r);
	a[u] = r != n;
	fs[u] = a[u] + fs[ls[u]] + fs[rs[u]];
	/* debug("%d - %d : %d {%d %d}\n", l, r, u, ls[u], rs[u]); */
	return u;
}

int main () {
	int t = read;
	read(n);
	for (int i = 1; i <= n - 3; i ++) {
		int x = read, y = read;
		S[x].insert(y);
		S[y].insert(x);
	}

	for (int i = 1; i < n; i ++) S[i].insert(i + 1);
	S[n].insert(1);
	for (int i = 2; i <= n; i ++) S[i].insert(i - 1);
	S[1].insert(n);

	build(1, n);

	ll fac = 1, mul = 1;
	int tot = 0;
	for (int i = 1; i <= np; i ++)
		if (a[i]) {
			(fac *= ++ tot) %= mod;
			(mul *= fs[i]) %= mod;
		}

	if (t)
		printf("%d %lld\n", tot, fac * power(mul, -1) % mod);
	else
		printf("%d\n", tot);

	int q = read;
	while (q --) {
		int x = read, y = read;
		/* int b = *S[y].upper_bound(x); */
		int d = *S[x].upper_bound(y);
		int u = map[par(x, y)];
		/* debug("%d\n", u); */

		int s = map[par(x, d)], r = rs[u], k = rs[s];

		ll bak = mul;
		(mul *= power(fs[u], -1)) %= mod;
		if (d != n) (mul *= fs[r] + fs[k] + 1) %= mod;
		else (fac *= power(tot --, -1)) %= mod;

		if (t)
			printf("%d %lld\n", tot, fac * power(mul, -1) % mod);
		else
			printf("%d\n", tot);

		mul = bak;
		if (d == n) (fac *= ++ tot) %= mod;
	}
}
