#if 0
2019.12.10

（不是给人做的）

首先由于列车都是每隔 k 个单位发一次，那么列车的行迹每连续 k 个单位是完全一致的，
因此只考虑连续 k 个单位时间的情况即可，此时时间成环，即第 k + 1 个单位等价于第 1 个单位，等等。

然后转化问题，设 p[i], q[i] 分别表示正向和反向列车离开第 i 站的时间，
那么在第 i 站到第 i + 1 站之间，正向列车在 [p[i], p[i] + a[i]] 时间段存在，
而反向列车在 [q[i + 1], q[i + 1] + a[i]] 时间段存在，
如果 b[i] = 1 ，需要满足两个区间无交，
也就是 p[i] - q[i + 1] <= - a[i] 或 >= a[i] 。

设 x[i] = p[i] - q[i + 1] ，那么 x[i] % k 需要在 [a[i], k - a[i]] 之内，
设这个区间为 [l[i], r[i]] 。
而由 p[i + 1] >= p[i] + a[i], q[i] >= q[i + 1] + a[i] 可知：
x[i + 1] >= x[i] + a[i] + a[i + 1] 。

不妨将 x[i + 1] 即以后整体减去 a[i] + a[i + 1] ，
那么对于所有满足 j > i 的 j ，需要把 l[j], r[j] 都减去 a[i] + a[i + 1] ，
每个 i （包括 i = 0 ）都进行这样的操作后，就把 x[i + 1] 的限制改成了 x[i + 1] >= x[i] ，
此时 l[i] = -2A[i - 1], r[i] = -2A[i] (mod k) ，其中 A 是 a 的前缀和。

至此，问题转换为，在长为 k 的环上有 n 个区间，
环上有位置 x ，初值任意，需要每次让 x 右移若干位来依次落入各个区间，
最小化 x 总共的移动次数（答案是这个移动次数加上 2A[n] ）。
其中 b = 2 的区间是整个环 (l = 0, r = k - 1) 。

先考虑贪心，如果 x 落在第 i 个区间的左端点 l[i]，那么对于第 i + 1 个区间，
如果 l[i] 落在第 i + 1 个区间内，x 不需要移动，否则 x 移动到 l[i + 1] 。

然后根据这个贪心设计 dp ，设 f[i] 表示考虑当前 x 落在 l[i] ，
走完剩下的区间需要的最小移动次数。
那么只需要找到一个 j > i 满足 (i, j) 之内的区间都包含 l[i] 且第 j 个区间不包含 l[i] ，
那么 x 在 (i, j) 之间的区间内都无需移动，直接从 f[j] 转移即可，
如果不存在这样的 j ，说明 x 之后永远无需移动，有 f[i] = 0 。

最后优化找 j 的过程，倒着 dp 时考虑 j 对 i 的影响时实际上是个区间覆盖，
用 odt 维护即可，由于只有单点查询，均摊复杂度最坏一个 log 。
#endif
#include <cstdio>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
ll a[maxn], b[maxn];
ll f[maxn];

struct Node {
	int r;
	mutable int v;
	Node(int r, int v = 0): r(r), v(v) { }
};
inline bool operator < (Node x, Node y) { return x.r < y.r; }

typedef std::set<Node>::iterator iter;
std::set<Node> odt;

inline iter split(int k) {
	iter it = odt.lower_bound(k);
	if(it -> r == k) return it;
	return odt.insert(Node(k, it -> v)).first;
}

inline void set(int l, int r, int v) {
	if(l > r) return;
	iter li = split(l - 1), ri = split(r);
	ri -> v = v;
	odt.erase(++ li, ri);
}

inline int query(int k) {
	iter it = odt.lower_bound(k);
	return it -> v;
}

int l[maxn], r[maxn];
int main() {
	int n = read, k = read;

	for(int i = 1; i <= n; i ++) {
		a[i] = a[i - 1] + read;
		b[i] = read;
		if(b[i] == 1) {
			l[i] = (k - a[i - 1] * 2 % k) % k;
			r[i] = (k - a[i] * 2 % k) % k;
			if((a[i] - a[i - 1]) * 2 > k) return puts("-1"), 0;
		} else {
			l[i] = 0;
			r[i] = k - 1;
		}
	}

	odt.insert(Node(k, n + 1));

	for(int i = n; i; i --) {
		int j = query(l[i]);
		if(j <= n)
			f[i] = f[j] + (l[j] - l[i] + k) % k;
		if(l[i] <= r[i]) {
			set(0, l[i] - 1, i);
			set(r[i] + 1, k - 1, i);
		} else
			set(r[i] + 1, l[i] - 1, i);
		/* debug("%d : %d-%d f=%lld j=%d\n", i, l[i], r[i], f[i], j); */
	}

	ll ans = 1000000000000000000ll;
	for(Node x : odt)
		if(x.r >= 0 and x.r < k) {
			/* debug("%d %d\n", x.r, x.v); */
			if(x.v <= n)
				ans = std::min(ans, f[x.v] + (l[x.v] - x.r + k) % k);
			else
				ans = 0;
		}
	ans += a[n] * 2;

	printf("%lld\n", ans);
}
