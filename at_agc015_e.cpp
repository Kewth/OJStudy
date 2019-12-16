#if 0
2019.12.16

足够长的时间后，点一定是按速度排序的，不妨假定 v 升序。
考虑点 i 被染色后有哪些点会被染到，事实上染到的一定是一段区间 [l, r] ，
l 是最小的满足 x[l] >= x[i] 的下标，
r 是最大的满足 x[r] <= x[i] 的下标。

原因：
i 最开始在 l 左边 (x[l] >= x[i])，最后一定会在 l 右边 (v[l] <= v[i]) ，
可以反证最后在 [l, i] 区间内的点都会被经过，
对于 r 同理。

求出了所有点的 [l, r] 后，问题转换为选择若干 [l, r] 使得它们的并为 [1, n] 。
根据定义不难发现 l, r 都随 x[i] 的增大单调不降。
那么再将点按 x 升序，此时的 l, r 也就都是升序的了。

DP 设 f[i] 表示用前 i 个区间，钦定第 i 个区间必选，覆盖 [1, r[i]] 的方案数。
对于所有满足 r[j] >= l[i] - 1 且 j < i 的 j 都可以从 f[j] 转移到 f[i] 。
而 r 是升序的，这意味着只要 f[j] 能转移到 f[i] ，f[j + 1] 就能转移到 f[i] ，
换言之，f[i] 的转移是一段区间 [L, i - 1] ，其中 L 是满足条件的最小 j 。
而同时 l 也是升序的，这意味着 L 也是升序的，dp 的过程中维护这个 L 即可。
区间转移用前缀和优化即可做到 O(1) 。

实现上并不需要反复排序，只需要将 x 离散化后就可以替代对 x 的排序，
并且 x 离散化后求 l, r 相当于求一类前缀后缀最值。
总复杂度 O(nlogn) ，瓶颈在于排序和离散化。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005, mod = 1000000007;
int l[maxn], r[maxn];
int p[maxn];
int tmp[maxn];
Par pr[maxn];
ll f[maxn], s[maxn];

int main() {
	int n = read;

	for(int i = 1; i <= n; i ++)
		read(pr[i].second, pr[i].first);
	std::sort(pr + 1, pr + n + 1);

	for(int i = 1; i <= n; i ++)
		tmp[i] = pr[i].second;
	std::sort(tmp + 1, tmp + n + 1);

	for(int i = 1; i <= n; i ++) {
		pr[i].second = int(std::lower_bound(tmp + 1, tmp + n + 1, pr[i].second) - tmp);
		p[pr[i].second] = i;
	}

	for(int i = 1; i <= n; i ++)
		r[i] = std::max(r[i - 1], p[i]);
	l[n] = p[n];
	for(int i = n - 1; i; i --)
		l[i] = std::min(l[i + 1], p[i]);

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug("%d-%d\n", l[i], r[i]); */

	int L = 0;
	f[0] = s[0] = 1;

	for(int i = 1; i <= n; i ++) {
		while(r[L] < l[i] - 1)
			++ L;
		f[i] = (s[i - 1] - s[L - 1] + mod) % mod;
		s[i] = (s[i - 1] + f[i]) % mod;
		/* debug("%lld\n", f[i]); */
	}

	while(r[L] < n)
		++ L;
	printf("%lld\n", (s[n] - s[L - 1] + mod) % mod);
}
