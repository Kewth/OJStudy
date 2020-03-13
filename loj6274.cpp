#if 0
2020.03.11

DP 套 DP ，计数的对象是 x & y ，那么钦定 T = x & y ，
然后考虑判断这个 T 是否可行。
判断的方式是数位 DP ，设 f[i][0/1][0/1][0/1][0/1] 表示考虑最高的 i 位，
是否满足了 Lx, Rx, Ly, Ry 的限制，这种情况下 T 是否可行。
但是要统计合法的 T 的数量，就需要在外层套一个 DP ，
设 F[i][S] 表示考虑最高的 i 位，有多少 T 满足其内层 DP 的结果是 S 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxk = 60;
ll f[maxk + 1][1 << 16];
bool g[16], h[2][16];

int main() {
	ll T = read, Lx = read, Rx = read, Ly = read, Ry = read;

	f[maxk][1 << 15] = 1;

	for(int k = maxk - 1; k >= 0; k --)
		for(int S = 0; S < (1 << 16); S ++)
			if(f[k + 1][S]) { // It's important!
				for(int i = 0; i < 16; i ++) {
					g[i] = S >> i & 1;
					h[0][i] = 0;
					h[1][i] = 0;
				}

				for(int x = 0; x < 2; x ++)
					for(int y = 0; y < 2; y ++)
						if((x | y) == (T >> k & 1))
							for(int i = 0; i < 16; i ++)
								if(g[i]) {
									int test = 
										(x < (Lx >> k & 1)) << 0 |
										(x > (Rx >> k & 1)) << 1 |
										(y < (Ly >> k & 1)) << 2 |
										(y > (Ry >> k & 1)) << 3;
									if(!(test & i)) {
										int j =
											(x == (Lx >> k & 1)) << 0 |
											(x == (Rx >> k & 1)) << 1 |
											(y == (Ly >> k & 1)) << 2 |
											(y == (Ry >> k & 1)) << 3;
										h[x & y][i & j] |= g[i];
									}
								}

				int T0 = 0, T1 = 0;
				for(int i = 0; i < 16; i ++) {
					T0 |= h[0][i] << i;
					T1 |= h[1][i] << i;
				}

				f[k][T0] += f[k + 1][S];
				f[k][T1] += f[k + 1][S];
			}

	ll ans = 0;
	for(int S = 1; S < (1 << 16); S ++)
		ans += f[0][S];
	printf("%lld\n", ans);
}
