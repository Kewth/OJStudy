#if 0
date +%Y.%m.%d

题解先咕着。
#endif
#include <cstdio>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 20, maxS = 1 << 10;
lolong f[maxn][maxn][maxS][2];
int N[maxn];

int dp(lolong n) {
	int p = 0;
	while(n) {
		N[++ p] = n % 10;
		n /= 10;
	}
	for(int i = 1; i <= p; i ++)
		for(int S = 0; S < maxS; S ++) {
			for(int k = 0; k < maxn; k ++)
				f[i][k][S][0] = f[i][k][S][1] = 0;
			for(int x = 0; x < 10; x ++) {
				int T = S;
				int now = 0;
				for(int k = x + 1; k < 10; k ++)
					if(T >> k & 1) {
						T ^= 1 << k;
						now ++;
					}
				T |= 1 << x;
				for(int k = 0; k + now < maxn; k ++) {
					f[i][k + now][S][0] += f[i - 1][k][T][0];
					if(x < N[i])
						f[i][k + now][S][1] += f[i - 1][k][T][0];
					else if(x == N[i])
						f[i][k + now][S][1] += f[i - 1][k][T][1];
					// debug("f[%d][%d][%d] = %lld, %lld\n",
							// i, k + now, S, f[i][k + now][S][0], f[i][k + now][S][1]);
					// if(i == 1 and k + now == 1 and S == 0)
						// debug("> %lld\n", f[1][1][0][1]);
				}
			}
			// if(S & 1)
				// for(int k = 0; k < maxn; k ++)
					// if(f[i][k][S][0] != f[i][k][S - 1][0]) {
						// debug("%d %d %d\n", i, k, S);
					// }
		}
	// debug("%lld, %lld\n", f[5][3][0][0], f[5][3][0][1]);
	// debug("%lld, %lld\n", f[4][3][0][0], f[4][3][0][1]);
	// debug("%lld, %lld\n", f[4][3][1][0], f[4][3][1][1]);
	// for(int x = 0; x < 10; x ++)
		// debug("%d: %lld, %lld\n", x, f[1][2][1 << x][0], f[1][2][1 << x][1]);
	return p;
}

int main() {
	for(int S = 0; S < maxS; S ++) {
		int now = 0;
		for(int k = 1; k < 10; k ++)
			if(S >> k & 1)
				now ++;
		f[0][now][S][0] = f[0][now][S][1] = 1;
	}
	lolong l = input(), r = input(), k = input();
	int p = dp(r);
	lolong ans = f[p][k][0][1];
	// debug("%lld\n", ans);
	p = dp(l - 1);
	ans -= f[p][k][0][1];
	printf("%lld\n", ans);
}
