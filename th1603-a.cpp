#if 0
2019.06.26

所有运算在模 9 意义下进行，发现每位可以选 0~8 ，
但是 0 有两个，不均匀，导致这题十分毒瘤。
把区间 [l, r] 改成两个端点 l - 1 和 r ，把所有 2Q 个端点排序。

先考虑所有端点两两不同。
相邻的端点 a, b 划出一段区间 [a + 1, b] ，考虑这段区间的方案。
枚举选 0 的个数，剩下的选 1~9 ，是均匀的，
那么在最后一个之前可以随便选，最后一个选唯一的一个就可以保证区间和为 x 。
特判全选零的情况，通过 (9 + 1)^n 的二项式定理可以得出：
当 s[a] != s[b]（区间和不为 0 ）时，区间方案为 (10^{b - a} - 1) / 9
当 s[a] = s[b]（区间和为 0 ）时，区间方案为 (10^{b - a} - 1) / 9 + 1
其中 s 表示前缀和，两者区别在于能否全选 0 。
区间 [l, r] 相当于要求 s[l - 1] = s[r] ，
那么枚举每个区间的 s 后，就可以得出一个贡献，答案就是 9^Q 种情况的贡献和。
设 f[i][S] 表示集合 S 的区间中有 i 种不同的 s ，
其他区间均视为 s 不同的贡献，转移枚举子集即可。
算贡献时需考虑 s 的组合，须注意的是，按上面的式子，第一个点的 s 是被钦定的。

至于有端点 a, b 相同的情况，相当于钦定几个区间的 s 必须相同。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

struct Dot {
	int p, id;
};

const int maxq = 16, mod = 1000000007;
lolong f[10][1 << maxq];
lolong choice[maxq << 1 | 1];
lolong more[maxq][maxq];
lolong trans[1 << maxq];
Dot d[maxq << 1];
int C[10][10], jie[10];
int fa[maxq];

inline int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

lolong power(lolong x, int k) {
	lolong res = 1;
	if(k < 0) k += mod - 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline bool cmp(Dot x, Dot y) { return x.p < y.p; }

int main() {
	C[0][0] = 1;
	for(int i = 1; i <= 9; i ++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	}
	jie[0] = 1;
	for(int i = 1; i <= 9; i ++)
		jie[i] = jie[i - 1] * i;
	int n = input(), q = input();
	for(int i = 0; i < q; i ++) {
		scanf("%d %d", &d[i * 2].p, &d[i * 2 + 1].p);
		d[i * 2].p --;
		d[i * 2].id = d[i * 2 + 1].id = i;
		fa[i] = i;
	}
	std::sort(d, d + q * 2, cmp);
	for(int i = 1; i < q * 2; i ++)
		if(d[i].p == d[i - 1].p)
			/* debug("%d -> %d\n", d[i].id, d[i - 1].id), */
			fa[find(d[i].id)] = find(d[i - 1].id);
	int U = 0;
	for(int i = 0; i < q; i ++)
		if(fa[i] == i)
			U |= 1 << i;
	/* debug("U=%d\n", U); */
	for(int i = 1; i < q * 2; i ++)
		choice[i] = (power(10, d[i].p - d[i - 1].p) + mod - 1)
			* power(9, -1) % mod;
	for(int i = 0; i < q; i ++)
		for(int j = 0; j < q; j ++)
			more[i][j] = 1;
	for(int i = 1; i < q * 2; i ++) {
		int a = find(d[i - 1].id), b = find(d[i].id);
		if(a > b) std::swap(a, b);
		if(choice[i])
			(more[a][b] *= (choice[i] + 1)
			 * power(choice[i], -1) % mod) %= mod;
	}
	f[0][0] = power(10, d[0].p + n - d[q * 2 - 1].p);
	for(int i = 1; i < q * 2; i ++)
		if(choice[i])
			(f[0][0] *= choice[i]) %= mod;
	for(int i = 0; i < q; i ++)
		(f[0][0] *= more[i][i]) %= mod;
	/* debug("base: %lld\n", f[0][0]); */
	lolong ans = 0;
	for(int S = U; S; S = (S - 1) & U) {
		trans[S] = 1;
		std::vector<int> v;
		for(int k = 0; k < q; k ++)
			if(S >> k & 1)
				v.push_back(k);
		for(int a : v)
			for(int b : v)
				if(a < b)
					(trans[S] *= more[a][b]) %= mod;
	}
	for(int i = 1; i <= 9; i ++) {
		for(int S = U; S; S = (S - 1) & U) {
			for(int T = S; T > 0; T = (T - 1) & S) {
				/* debug("f[%d][%d] += f[%d][%d](%lld) * %lld\n", */
				/* 		i, S, i - 1, S - T, f[i - 1][S - T], trans[T]); */
				(f[i][S] += f[i - 1][S ^ T] * trans[T] % mod) %= mod;
			}
			(f[i][S] *= power(i, -1)) %= mod;
			/* debug("f[%d][%d] = %lld\n", i, S, f[i][S]); */
		}
		lolong now = f[i][U];
		(now *= C[8][i - 1]) %= mod;
		(now *= jie[i -  1]) %= mod;
		(ans += now) %= mod;
	}
	printf("%lld\n", ans);
}
