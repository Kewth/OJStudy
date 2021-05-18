#if 0
2019.06.19

讲道理 k 不同做法是不同的，事实上 k 的做法可以转换为 k + 1 的做法。
加一个很大的区间 [x, x] 同时把 s 加上 x 即可。

相当于要求一些无序 4 元组，
神仙容斥，计算有序 4 元组 abcd 的数量，会重复计算 4! 次，除去 24 。
因为要求 abcd 互不相同，考虑 aabc, aabb, aaab, aaaa 容斥（注意是有序）。
容斥的情况：
abcd -> aabc 6 C42
abcd -> aabb 3 C42/2
abcd -> aaab 4 C43
abcd -> aaaa 1 C44
aabc -> aabb 1 C11
aabc -> aaab 2 C21
aabc -> aaaa 1 C22
aabb -> aaab 0
aabb -> aaaa 1 C11
aaab -> aaaa 1 C11

然后除 abcd 外其他都可以在 n^3 内爆搞出来。
abcd 此时是有序且允许相等的数的。

继续神仙差分容斥。
把区间 [l, r] 分成两个区间 [l, s] 和 [r + 1, s] ，后者在算贡献时需乘 -1 。
把所有区间这样分，那么选若各个区间都是一段后缀，贡献乘上它们的 1/-1 积。
问题转换为 800 个形如 [x, s] 的区间。

若选中 k 个区间 [a, s], [b, s], [c, s], [d, s] (a + b + c + d <= s),
那么它们的贡献就是 (s - a - b - c - d) 个相同球放进 4 个不同可空盒子的方案。
类似 meet in middle, 利用组合数公式 C(s - a - b + 3, 3) =
+ C(s - a + 3, 3) * C(- b, 0)
+ C(s - a + 3, 2) * C(- b, 1)
+ C(s - a + 3, 1) * C(- b, 2)
+ C(s - a + 3, 0) * C(- b, 3) 和单调性优化。
需预处理逆元，不然会带一个 log 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

struct Node {
	lolong p, v;
	Node(lolong p = 0, lolong v = 0): p(p), v(v) {}
};
const int maxn = 404, mod = 1000000007;
lolong l[maxn], r[maxn];
Node b[maxn << 1], d[maxn * maxn * 4];

inline bool cmp(Node x, Node y) {
	return x.p == y.p ? x.v < y.v : x.p < y.p;
}

inline lolong inv(lolong x) {
	switch(x) {
		case 1: return 1;
		case 2: return 500000004;
		case 3: return 333333336;
		case 4: return 250000002;
	}
	lolong res = 1;
	int k = mod - 2;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline lolong C(lolong n, int m) {
	lolong res = 1;
	for(int i = 1; i <= m; i ++)
		(res *= (n - i + 1) * inv(i) % mod) %= mod;
	return res;
}

int main() {
	int n = input(), k = input();
	lolong s = input();
	for(int i = 0; i < n; i ++) {
		l[i] = input();
		r[i] = input();
	}
	if(k <= 3) {
		l[n] = r[n] = s * 3;
		n ++;
		s += s * 3;
	}
	if(k <= 2) {
		l[n] = r[n] = s * 3;
		n ++;
		s += s * 3;
	}
	for(int i = 0; i < n; i ++) {
	 	b[i * 2] = Node(l[i], 1);
		b[i * 2 + 1] = Node(r[i] + 1, -1);
	}
	int N = n * 2;
	for(int i = 0; i < N; i ++)
		for(int j = 0; j < N; j ++)
			d[i * N + j] = Node(b[i].p + b[j].p, b[i].v * b[j].v);
	std::sort(b + 1, b + N, cmp);
	std::sort(d + 1, d + N * N, cmp);
	lolong ans = 0;
	// aaaa
	{
		lolong now = 0;
		if(s % 4 == 0)
			for(int i = 0; i < N; i ++)
				if(b[i].p <= s / 4)
					now += b[i].v;
		ans -= 6 * now % mod;
		debug("aaaa %lld %lld\n", now, mod - now * 6);
	}
	// aabb
	{
		lolong now = 0;
		if(s % 2 == 0)
			for(int i = 0; i < N * N; i ++)
				if(d[i].p <= s / 2)
					now += (s / 2 - d[i].p + 1) * d[i].v % mod;
		ans += 3 * now % mod;
		debug("aabb %lld %lld\n", now, 3 * now);
	}
	// aaab
	{
		lolong now = 0;
		for(int i = 0; i < N; i ++)
			for(int j = 0; j < N; j ++)
				if(b[i].p * 3 + b[j].p <= s)
					now += ((s - b[i].p * 3 - b[j].p) / 3 + 1)
						* b[i].v * b[j].v % mod;
		ans += 8 * now % mod;
		debug("aaab %lld %lld\n", now, 8 * now);
	}
	// aabc
	{
		lolong now = 0, sum = 0, ssum = 0;
		int p = 0, tot = 0;
		for(int i = N * N - 1; i >= 0; i --) {
			if(d[i].p > s) continue;
			while(p < N and d[i].p + b[p].p * 2 <= s) {
				tot += b[p].v;
				(sum += b[p].p * b[p].v) %= mod;
				(ssum += b[p].p % mod * b[p].p % mod * b[p].v) %= mod;
				p ++;
			}
			lolong down = ((s - d[i].p) / 2 + 1) % mod;
			lolong up = ((s - d[i].p + 1) / 2 + 1) % mod;
			(now += (tot * up % mod * down - (up + down) * sum + ssum)
				* d[i].v % mod) %= mod;
		}
		(now += mod) %= mod;
		ans -= 6 * now % mod;
		debug("aabc %lld %lld\n", now, (mod - now * 6 % mod) % mod);
	}
	// abcd
	{
		lolong now = 0, sum[4] = {0, 0, 0, 0};
		int p = 0;
		for(int i = N * N - 1; i >= 0; i --) {
			if(d[i].p > s) continue;
			while(p < N * N and d[i].p + d[p].p <= s) {
				for(int j = 0; j < 4; j ++)
					(sum[j] += C(- d[p].p, j) * d[p].v) %= mod;
				p ++;
			}
			for(int j = 0; j < 4; j ++)
				(now += d[i].v * C(s - d[i].p + 3, j)
				 * sum[4 - j - 1]) %= mod;
		}
		ans += now % mod;
		debug("abcd %lld\n", now);
	}
	(ans %= mod) += mod;
	(ans *= inv(24)) %= mod;
	printf("%lld\n", ans);
}
