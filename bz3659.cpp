#if 0
2019.09.27

BEST 引理模板，特别的是本题规定路径顺序不同为不同方案，
因此每一个欧拉回路的贡献不是 1 ，而是起点的度。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 105, maxm = 200005, mod = 1000003;
lolong ma[maxn][maxn];
lolong fac[maxm];

int main() {
	fac[0] = 1;
	for(int i = 1; i < maxm; i ++)
		fac[i] = fac[i - 1] * i % mod;

	while(1) {
		int n = input();
		if(!n) break;
		lolong ans = 1;

		for(int i = 2; i <= n; i ++)
			for(int j = 2; j <= n; j ++)
				ma[i][j] = 0;

		for(int i = 1; i <= n; i ++) {
			int k = input();
			ma[i][i] += k;
			if(i == 1) (ans *= fac[k]) %= mod;
			else (ans *= fac[k - 1]) %= mod;
			while(k --)
				ma[i][input()] --;
		}

		for(int i = 2; i <= n; i ++)
			for(int j = 2; j <= n; j ++)
				ma[i][j] += mod;

		for(int i = 2; i <= n; i ++)
			for(int j = i + 1; j <= n; j ++)
				while(ma[j][i]) {
					lolong d = ma[i][i] / ma[j][i];
					for(int k = i; k <= n; k ++)
						(ma[i][k] += mod - d * ma[j][k] % mod) %= mod;
					std::swap(ma[i], ma[j]);
					ans *= -1;
				}

		ans += mod;
		for(int i = 2; i <= n; i ++)
			(ans *= ma[i][i]) %= mod;
		ans %= mod;

		printf("%lld\n", ans);
	}
}
