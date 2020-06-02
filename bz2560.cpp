/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.02

 * Solution:
  直接状压 DP 设 f[S] 表示点集 S 的答案，用容斥进行转移，用总方案减去不连通方案，不连通
的方案只需要枚举 S 的任意一个点 p 所在的联通块即可。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 16, mod = 1000000007;
ll g[1 << maxn];
ll f[1 << maxn];
int a[maxn][maxn];

int main () {
	int n = read;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			read(a[i][j]);

	for (int S = 0; S < (1 << n); S ++) {
		g[S] = 1;
		for (int i = 0; i < n; i ++)
			for (int j = 0; j < i; j ++)
				if (S >> i & 1 and S >> j & 1)
					(g[S] *= a[i][j] + 1) %= mod;
	}

	f[0] = 1;
	for (int S = 1; S < (1 << n); S ++) {
		f[S] = g[S];
		int p = 0;
		while (!(S >> p & 1)) ++ p;
		int A = S ^ (1 << p);
		for (int T = A - 1; T >= 0; T --) {
			T &= A;
			int B = T ^ (1 << p);
			(f[S] += (mod - f[B]) * g[S ^ B]) %= mod;
		}
	}

	printf("%lld\n", f[(1 << n) - 1]);
}
