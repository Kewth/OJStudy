#if 0
2019.08.27

三个乘不方便按照位运算的一般套路直接枚举每一位算贡献。
但可以考虑枚举 (a[i] ^ a[k]) 的每一位算贡献。
枚举 j ，问题转换为求 j 左边的 (a[i] ^ a[j]) 和与 (a[j] ^ a[k]) 和，
由于枚举了 (a[i] ^ a[k]) 在 b 位为 1 ，还要把 (a[i] ^ a[j]) 按照 a[i][b] 分开算，
(a[j] ^ a[k]) 也是同理，一共算出四个部分后就可以算贡献了。
而算 (a[i] ^ a[j]) 的和就是典型的按套路分每一位算贡献的类型。
也就是说，这个统计是枚举位数套枚举位数，复杂度 O(n logn logn) 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, maxk = 31, mod = 998244353;
int a[maxn];
int l[2][maxk], r[2][maxk];

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();

	lolong ans = 0;

	for(int k = 0; k < maxk; k ++) {

		for(int kk = 0; kk < maxk; kk ++)
			l[0][kk] = l[1][kk] = r[0][kk] = r[1][kk] = 0;

		for(int i = n; i > 1; i --)
			for(int kk = 0; kk < maxk; kk ++)
				r[a[i] >> k & 1][kk] += a[i] >> kk & 1;

		int lk[2] = {0, 0}, rk[2] = {0, 0};
		for(int i = n; i > 1; i --)
			rk[a[i] >> k & 1] ++;

		lolong now = 0;
		for(int i = 2; i < n; i ++) {
			for(int kk = 0; kk < maxk; kk ++)
				l[a[i - 1] >> k & 1][kk] += a[i - 1] >> kk & 1;
			for(int kk = 0; kk < maxk; kk ++)
				r[a[i] >> k & 1][kk] -= a[i] >> kk & 1;

			lk[a[i - 1] >> k & 1] ++;
			rk[a[i] >> k & 1] --;

			lolong l0 = 0, l1 = 0, r0 = 0, r1 = 0;
			for(int kk = 0; kk < maxk; kk ++)
				if(a[i] >> kk & 1) {
					l0 += (1ll << kk) * (lk[0] - l[0][kk]);
					l1 += (1ll << kk) * (lk[1] - l[1][kk]);
					r0 += (1ll << kk) * (rk[0] - r[0][kk]);
					r1 += (1ll << kk) * (rk[1] - r[1][kk]);
				} else {
					l0 += (1ll << kk) * l[0][kk];
					l1 += (1ll << kk) * l[1][kk];
					r0 += (1ll << kk) * r[0][kk];
					r1 += (1ll << kk) * r[1][kk];
				}

			l0 %= mod;
			l1 %= mod;
			r0 %= mod;
			r1 %= mod;

			/* for(int kk = 0; kk < maxk; kk ++) */
			/* 	debug("%d", l[0][kk]); */
			/* debug("\n"); */
			/* for(int kk = 0; kk < maxk; kk ++) */
			/* 	debug("%d", a[i] >> kk & 1); */
			/* debug("\n"); */
			/* debug("%lld %lld %lld %lld\n", l0, l1, r0, r1); */

			(now += l0 * r1 + l1 * r0) %= mod;
		}

		/* debug("%lld\n", now); */

		ans += now * (1 << k) % mod;
	}

	printf("%lld\n", ans % mod);
}
