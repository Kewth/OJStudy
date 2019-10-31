#if 0
2019.10.30

设两点边权为两点编号最大值，那么询问就是询问走权值不超过 y 的边的联通块，
Kurskal 重构树，倍增维护向上的路径，线段树维护区间乘积。

坑，a 的范围是 [1, 1e9] ，可能恰好为 998244353 ，从而没有逆元，对树状数组极不友好。
本来尝试者不写 dfs 维护 Kurskal 重构树，结果发现由于每个点对应的叶子需要是区间，
那么就需要 dfs 序，而不进行 dfs 似乎是没法获得 dfs 序的。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 2000005, maxk = 20, mod = 998244353;

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

ll val[maxn * 3];
int n;
ll query(int l, int r, int now = 1, int L = 1, int R = n) {
	if(l > R or r < L) return 1;
	if(l <= L and R <= r) return val[now];
	int M = (L + R) >> 1;
	return query(l, r, now << 1, L, M) * query(l, r, now << 1 | 1, M + 1, R) % mod;
}

void modify(int p, int x, int now = 1, int L = 1, int R = n) {
	if(L == R)
		return val[now] = x, void();
	int M = (L + R) >> 1;
	if(p <= M) modify(p, x, now << 1, L, M);
	else modify(p, x, now << 1 | 1, M + 1, R);
	val[now] = val[now << 1] * val[now << 1 | 1] % mod;
}

int ex[maxn], ey[maxn], p[maxn];
bool cmp(int x, int y) {
	return std::max(ex[x], ey[x]) < std::max(ex[y], ey[y]);
}

int top[maxn];
int fa[maxn][maxk], max[maxn][maxk];
int find(int x) {
	if(top[x] == x) return x;
	return top[x] = find(top[x]);
}

int l[maxn], r[maxn], ip;
int ls[maxn], rs[maxn];
int a[maxn];
void dfs(int u) {
	for(int k = 1; k < maxk; k ++) {
		fa[u][k] = fa[fa[u][k - 1]][k - 1];
		max[u][k] = std::max(max[u][k - 1], max[fa[u][k - 1]][k - 1]);
	}
	if(u <= n)
		modify(l[u] = r[u] = ++ ip, a[u]);
	else {
		dfs(ls[u]);
		dfs(rs[u]);
		l[u] = l[ls[u]];
		r[u] = r[rs[u]];
	}
}

int main() {
	read(n);
	int m = read, q = read;

	for(int i = 0; i < maxn * 3; i ++)
		val[i] = 1;

	for(int i = 1; i <= n; i ++)
		a[i] = read % mod;

	for(int i = 1; i <= m; i ++)
		read(ex[p[i] = i], ey[i]);

	std::sort(p + 1, p + m + 1);

	int d = n;
	for(int i = 1; i <= n; i ++)
		l[i] = r[i] = top[i] = i;

	for(int i = 1; i <= m; i ++) {
		int x = ex[p[i]], y = ey[p[i]];
		if(find(x) == find(y)) continue;
		int w = std::max(x, y);
		x = find(x);
		y = find(y);
		*fa[x] = *fa[y] = ++ d;
		*max[x] = *max[y] = w;
		l[d] = std::min(l[x], l[y]);
		r[d] = std::max(r[x], r[y]);
		top[x] = top[y] = top[d] = d;
		ls[d] = x;
		rs[d] = y;
		/* debug("%d %d -> %d\n", x, y, d); */
	}

	dfs(d);

	while(q --) {
		if(read == 1) {
			int u = read, x = read;
			if(u > x) puts("0");
			else {
				for(int k = maxk - 1; k >= 0; k --)
					if(fa[u][k] and max[u][k] <= x)
						u = fa[u][k];
				/* debug("%d : %d %d\n", u, l[u], r[u]); */
				printf("%lld\n", query(l[u], r[u]));
			}
		}

		else {
			int u = read, x = read % mod;
			modify(l[u], x);
		}
	}
}
