#if 0
2019.12.17

对于两个可以交换的点连边，那么一个联通块的点是可以任意排布顺序的。
直接连边的复杂度是 O(n^2) ，但是由于只需要关注图的连通性，可以优化建图。

首先对于颜色 C 内的点只需要对于每个点 u 考虑是否能连 k 即可，
其中 k 是颜色 C 中重量最小的点。

对于颜色不同的点，首先找到全局重量最小的点 k ，其颜色为 c[k] ，
那么对于点 u 如果 c[u] != c[k] ，只需考虑 u, k 是否能连边即可。
但这样不够，还需找到除去 c[k] 外的重量最小的点 k2 ，
对于 c[u] != c[k2] 的点 u 再考虑 u, k2 之间的连边。

连边后统计每个联通块的贡献乘起来，每个联通块的贡献就是一些组合数相乘。
#endif
#include <cstdio>
#include <vector>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005, mod = 1000000007;
int color[maxn], weight[maxn];
std::vector<int> con[maxn];
int min[maxn];
int fa[maxn];
std::map<int, int> map[maxn];
ll fac[maxn], ifac[maxn];

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

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

inline void merge(int x, int y) {
	/* debug("%d - %d\n", x, y); */
	x = find(x);
	y = find(y);
	fa[x] = y;
}

int main() {
	int n = read, x = read, y = read;
	weight[0] = 2000000000;

	for(int i = 1; i <= n; i ++) {
		read(color[i], weight[i]);
		con[color[i]].push_back(i);
		if(weight[i] < weight[min[color[i]]])
			min[color[i]] = i;
	}

	for(int i = 1; i <= n; i ++)
		fa[i] = i;

	int minc = 0, minc2 = 0;
	for(int c = 1; c <= n; c ++)
		if(weight[min[c]] < weight[min[minc]]) {
			minc2 = minc;
			minc = c;
		} else if(weight[min[c]] < weight[min[minc2]])
			minc2 = c;

	/* debug("%d %d\n", minc, minc2); */

	for(int c = 1; c <= n; c ++)
		for(int p : con[c])
			if(weight[p] + weight[min[c]] <= x)
				merge(p, min[c]);

	for(int c = 1; c <= n; c ++)
		for(int p : con[c]) {
			if(c != minc and weight[p] + weight[min[minc]] <= y)
				merge(p, min[minc]);
			if(c != minc2 and weight[p] + weight[min[minc2]] <= y)
				merge(p, min[minc2]);
		}

	for(int i = 1; i <= n; i ++)
		++ map[find(i)][color[i]];

	ll ans = 1;

	fac[0] = 1;
	for(int i = 1; i <= n; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[n] = power(fac[n], -1);
	for(int i = n; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	for(int i = 1; i <= n; i ++)
		if(fa[i] == i) {
			int tot = 0;
			for(auto pr : map[i]) {
				tot += pr.second;
				(ans *= ifac[pr.second]) %= mod;
				/* debug("%d in %d\n", pr.second, i); */
			}
			(ans *= fac[tot]) %= mod;
		}

	printf("%lld\n", ans);
}
