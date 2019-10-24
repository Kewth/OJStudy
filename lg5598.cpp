#if 0
2019.10.24

枚举左端点 l 再枚举右端点 r ， f(l, r) 就是 f(l, r - 1) 乘上一个组合数。
暴力枚举 r ，如果 a 都是正数那么 f(l, r) 最多在 p logV 次枚举后模 p 为 0 。
但是有 0 ，一段 0 的贡献是一样的，可以把一段连续的 0 缩到一起。
每次算组合数可以用卢卡斯，复杂度 O(n p log^2V) 。
然后一个看上去很 sb 但实际上能优化复杂度的做法是预处理 a 在卢卡斯的每个数去做。

具体来讲，卢卡斯的本质就是把数转成 p 进制然后逐个计算，
而 f(l, r) 最多枚举 p logV 次的原因是只要当前区间和在 p 进制上有进位就会 gg ，
p 进制上就会有一位的数比和要小，导致组合数为 0 。
那事实上最多枚举 p logV 个正数的本质是因为区间和最多发生 p logV 次改变就一定有进位。
本质上还是去 0 ，只考虑 a 的每个非 0 位加到区间和里，这样每次发生改变可以 O(1) 算组合数。
故复杂度 O(n p logV) 。
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 500005, maxp = 10;
lolong a[maxn];
const int maxc = 1000;
int c[maxc][maxc];
int not0[maxn];
int pval[maxn][60], pid[maxn][60], pp[maxn];

int p;
int C(lolong n, lolong m) {
	if(m > n) return 0;
	if(n < maxc and m < maxc) return c[n][m];
	return C(n / p, m / p) * c[n % p][m % p] % p;
}

int main() {
	int n = input();
	p = input();

	for(int i = 0; i < maxc; i ++) {
		c[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % p;
	}

	for(int i = 1; i <= n; i ++) {
		a[i] = linput();
		int k = 0;
		for(lolong x = a[i]; x; x /= p) {
			k ++;
			if(x % p) {
				pval[i][++ pp[i]] = x % p;
				pid[i][pp[i]] = k;
			}
		}
	}

	not0[n + 1] = n + 1;
	for(int i = n; i; i --)
		if(a[i])
			not0[i] = i;
		else
			not0[i] = not0[i + 1];

	/* for(int i = 1; i <= n; i ++) */
	/* 	debug("%d\n", not0[i]); */

	lolong ans = 0;
	for(int l = 1; l <= n; l ++) {
		int f = 1;
		int sum[60];
		memset(sum, 0, sizeof sum);

		for(int r = l; r <= n; r ++) {
			int k = r;
			r = not0[r];
			ans += 1ll * (r - k) * f;
			if(r > n) break;

			for(int i = 1; i <= pp[r]; i ++) {
				sum[pid[r][i]] += pval[r][i];
				if(sum[pid[r][i]] >= p) {
					f = 0;
					break;
				}
				/* debug("%d %d -> %d\n", */
				/* 		sum[pid[r][i]], pval[r][i], c[sum[pid[r][i]]][pval[r][i]]); */
				(f *= c[sum[pid[r][i]]][pval[r][i]]) %= p;
			}

			if(!f) break;
			/* debug("%d - %d : %d\n", l, r, f); */
			ans += f;
		}
	}

	printf("%lld\n", ans);
}
