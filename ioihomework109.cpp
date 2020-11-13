/*
 * Author: Kewth

 * Date:
  2020.11.06

 * Solution:
  In blog.

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ull () { ull x; return scanf("%llu", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

__int128 exgcd (__int128 a, __int128 b, __int128 &x, __int128 &y) {
	if (!b) return x = 1, y = 0, a;
	__int128 res = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return res;
}

const int maxn = 64, maxm = 21;
ull a[maxn], b[maxn];
std::map<ull, int> map;
ull sum[1 << maxm];
char ans[maxn + 1];

int main () {
	int n = read;
	for (int i = 0; i < n; i ++) read(b[i]);
	ull s = read;

	if (n <= maxm * 2) {
		int m = n >> 1;
		for (int i = 0; i < m; i ++)
			sum[1 << i] = b[i];
		for (int S = 0; S < (1 << m); S ++) {
			sum[S] = sum[S & (S - 1)] + sum[S & -S];
			map[sum[S]] = S;
		}
		for (int i = 0; i < n - m; i ++)
			sum[1 << i] = b[m + i];
		for (int S = 0; S < (1 << (n - m)); S ++) {
			sum[S] = sum[S & (S - 1)] + sum[S & -S];
			if (map.count(s - sum[S])) {
				int T = map[s - sum[S]];
				for (int i = 0; i < m; i ++)
					putchar(T >> i & 1 ? '1' : '0');
				for (int i = 0; i < n - m; i ++)
					putchar(S >> i & 1 ? '1' : '0');
				return 0;
			}
		}
	}

	else {
		ull lim = (1 - (1llu << (n - 1))) >> (n - 1);
		for (ull a0 = 1; a0 <= lim; a0 ++) {
			ull A = a0, B = b[0], C;
			__int128 Q = __int128(1) << 64;
			int k = 0;
			while (!(B & 1)) {
				if (A & 1) goto fail;
				++ k;
				A >>= 1, B >>= 1, Q >>= 1;
			}
			__int128 inv, tmp;
			exgcd(B, Q, inv, tmp);
			inv %= Q;
			if (inv < 0) inv += Q;
			C = ull(inv) * A % Q;
			if (!(C & 1)) goto fail;
			for (int t = 0; t < (1 << k); t ++) {
				__int128 pre = 0;
				bool ok = 1;
				for (int i = 0; i < n; i ++) {
					a[i] = b[i] * C;
					ok &= a[i] > pre;
					pre += a[i];
				}
				ok &= (pre >> 64) == 0;
				if (ok) {
					ull S = s;
					S *= C;
					for (int i = n - 1; i >= 0; i --)
						if (S >= a[i])
							S -= a[i], ans[i] = '1';
						else
							ans[i] = '0';
					if (!S) {
						/* ull test = 0; */
						/* for (int i = 0; i < n; i ++) */
						/* 	if (ans[i] == '1') */
						/* 		test += b[i]; */
						/* if (test != s) */
						/* 	return 2; */
						return puts(ans), 0;
					}
				}
				C += Q;
			}
fail:;
		}
	}

	return 1;
}
