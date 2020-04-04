#if 0
2020.02.15

对于函数 D(i^x) ，将 i 看作常量，就是关于 x 的 k 次多项式，
其中 k 是 i 的质因子个数，i 在 1e7 内 k 最大为 8 。
那么筛出 1e7 内所有 D(i^x) 表示的多项式，然后求前缀和即可简单处理询问。
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

const int maxn = 10000005, mod = 998244353;
int minp[maxn], ppow[maxn];
short pk[maxn], size[maxn];
int poly[maxn][9];

int main() {
	int N = 10000000;
	minp[1] = 1;
	poly[1][0] = 1;
	for(int i = 2; i <= N; i ++) {
		int &p = minp[i];
		if(!p) {
			p = i;
			if(i <= N / i)
				for(int j = i * i; j <= N; j += i)
					if(!minp[j])
						minp[j] = p;
		}

		int j = i / p;
		pk[i] = minp[j] == p ? pk[j] + 1 : 1;
		ppow[i] = minp[j] == p ? ppow[j] * p : p;
		size[i] = minp[j] == p ? size[j] : size[j] + 1;

		j = i / ppow[i];
		poly[i][0] = 1;
		for(int k = 1; k <= size[i]; k ++)
			poly[i][k] = poly[j][k - 1] * pk[i] + poly[j][k];
	}

	for(int i = 1; i <= N; i ++)
		for(int k = 0; k <= 8; k ++)
			(poly[i][k] += poly[i - 1][k]) %= mod;

	int q = read;
	while(q --) {
		int n = read, x = read;
		ll now = 1, ans = 0;
		for(int k = 0; k <= 8; k ++) {
			(ans += now * poly[n][k]) %= mod;
			(now *= x) %= mod;
		}
		printf("%lld\n", ans);
	}
}
