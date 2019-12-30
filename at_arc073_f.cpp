#if 0
2019.12.30

朴素 dp 设 f[i][p][q] 表示前 i 次操作后当前棋子为 (p, q) 的最小代价。
事实上由于第 i 次操作后一定有一个棋子是 x[i] ，因此可以优化一维：
f[i][j] 表示前 i 次操作后当前棋子为 (j, x[i]) 的最小代价。

转移有两种：
1) f[i - 1][j] + |x[i - 1] - x[i]| -> f[i][j]
2) min(f[i - 1][k] + |x[i] - k|) -> f[i][x[i - 1]]
用线段树维护 f[~][j] ，第一种转移就是全局加，第二种是单点取 min 。
第二种转移可以把左边的绝对值拆开：
f[i - 1][k] - k + x[i] (k < x[i])
f[i - 1][k] (k = x[i])
f[i - 1][k] + k - x[i] (k > x[i])
线段树分别维护 f[~][j] - j, f[~][j], f[~][j] + j 即可。
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

const int maxn = 200005;
ll f[maxn << 2], fa[maxn << 2], fb[maxn << 2], tag;

void modify(int now, int L, int R, int p, ll x) {
	f[now] = std::min(f[now], x);
	fa[now] = std::min(fa[now], x + p);
	fb[now] = std::min(fb[now], x - p);
	if(L == R) return;
	int M = (L + R) >> 1;
	if(p <= M) modify(now << 1, L, M, p, x);
	else modify(now << 1 | 1, M + 1, R, p, x);
}

void build(int now, int L, int R) {
	f[now] = fa[now] = fb[now] = 1000000000000000000;
	if(L == R) return;
	int M = (L + R) >> 1;
	build(now << 1, L, M);
	build(now << 1 | 1, M + 1, R);
}

ll query(int now, int L, int R, int p) {
	if(R < p) return p + fb[now];
	if(L > p) return fa[now] - p;
	if(L == R) return f[now];
	int M = (L + R) >> 1;
	return std::min(query(now << 1, L, M, p), query(now << 1 | 1, M + 1, R, p));
}

int main() {
	int n = read, q = read, a = read, b = read;

	build(1, 1, n);
	modify(1, 1, n, a, 0);
	/* modify(1, 1, n, b, 0); */

	int last = b;
	while(q --) {
		int x = read;
		ll qu = query(1, 1, n, x) + tag;
		/* debug("qu = %lld\n", qu); */
		tag += std::abs(x - last);
		modify(1, 1, n, last, qu - tag);
		last = x;
		/* debug("tag=%lld\n", tag); */
	}

	printf("%lld\n", f[1] + tag);
}
