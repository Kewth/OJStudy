#if 0
2019.11.15

将区间按二进制拆分，分为 O(log) 个长为 2^k 的区间，
（事实上这是可重的，类似于 st 表的 O(1) 查询可以分为两个长为 2^k 的区间）
对于每个 k 单独维护并查集，把长度为 2^k 的必须相同的区间左端点合并至一个并查集，
不难发现如果所有区间长为 1 ，那么对于 k = 0 的并查集，答案就是 9 * 10^|集合个数 - 1| ，
而对于每个 k > 0 ，可以将每个长 2^k 的区间拆成两个长 2^(k-1) 的区间，
将每个集合的并查集下传到 k - 1 这个维度即可。
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

const int maxn = 100005, maxk = 18, mod = 1000000007;
int fa[maxn][maxk];

int find(int x, int k) {
	if(fa[x][k] == x) return x;
	return fa[x][k] = find(fa[x][k], k);
}

inline void merge(int x, int y, int k) {
	x = find(x, k);
	y = find(y, k);
	if(x != y) fa[x][k] = y;
}

int main() {
	int n = read, m = read;

	for(int i = 1; i <= n; i ++)
		for(int k = 0; k < maxk; k ++)
			fa[i][k] = i;

	for(int i = 1; i <= m; i ++) {
		int l1 = read, r1 = read, l2 = read, r2 = read;
		int len = r1 - l1 + 1;
		if(l1 > l2) std::swap(l1, l2);
		for(int k = maxk - 1; k >= 0; k --)
			if(len >> k & 1) {
				merge(l1, l2, k);
				l1 += 1 << k;
				l2 += 1 << k;
			}
	}

	for(int k = maxk - 1; k; k --)
		for(int i = 1; i + (1 << k) - 1 <= n; i ++) {
			merge(i, find(i, k), k - 1);
			merge(i + (1 << (k - 1)), find(i, k) + (1 << (k - 1)), k - 1);
		}

	int k = 0;
	for(int i = 1; i <= n; i ++)
		if(fa[i][0] == i)
			++ k;

	ll ans = 9;
	for(int i = 1; i < k; i ++)
		(ans *= 10) %= mod;

	printf("%lld\n", ans);
}
