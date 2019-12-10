#if 0
2019.12.10

对于凸包点集 S ，其贡献为 2^k ，其中 k 是该凸包包含的点数除去顶点。
设 T 表示这 k 个点组成的集合，那么 2^k 就是 T 的子集数量。

那么每个 (S, U) 二元组对答案的贡献为 1 ，其中 U 是 T 的子集。
而事实上 (S, U) 与 S 并 U 是一一对应的，
因为一个点集的凸包是唯一的，也就是说已知 S 并 U 可以求出唯一的 S ，进而求出唯一的 U 。
那么答案就是合法的 S 并 U 的点集数量。

合法指的是什么？指的就是存在凸包。
那么什么样的点集不合法呢？一个点集 X 不合法当且仅当 X 的点共线或者 |X| < 3 。

那么可以简单容斥，用满足 |X| >= 3 的 X 的数量减去不合法的 X 数量。
也就是统计共线的点集数，n 很小，枚举两个点，它们唯一确定一条直线，
然后再暴力统计该直线上有多少点即可，这样一个 X 会被算多次，除掉算重次数即可。

另外也可以枚举共线 X 的两个端点，然后暴力统计端点构成的线段之间有多少点，设为 k ，
那么这两个端点对不合法点集的贡献就是 2^k ，这样的好处是不会算重，更好理解。

总复杂度 O(n^3) ，事实上统计一条直线上的点数有更优秀的做法，可以做到 O(n^2logn) ，
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 205, mod = 998244353;

inline ll sq(ll x) { return x * x; }
inline bool in_line(ll x1, ll y1, ll x2, ll y2) {
	ll a = x1 * x2 + y1 * y2;
	ll b = (sq(x1) + sq(y1)) * (sq(x2) + sq(y2));
	return a >= 0 and sq(a) == b;
}

int x[maxn], y[maxn];
ll p2[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		read(x[i], y[i]);

	p2[0] = 1;
	for(int i = 1; i <= n; i ++)
		p2[i] = (p2[i - 1] << 1) % mod;

	ll ans = p2[n] - n - 1;

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j < i; j ++) {
			int tot = 0;
			for(int k = 1; k <= n; k ++)
				if(k != i and k != j and
						in_line(x[i] - x[k], y[i] - y[k], x[k] - x[j], y[k] - y[j]))
					debug("%d %d %d\n", i, k, j),
					++ tot;
			ans -= p2[tot];
		}

	printf("%lld\n", (ans % mod + mod) % mod);
}
