#if 0
2019.05.18

数位 DP ?
统计每个 sum(i) = k 的数量。
蛋疼的是 mod 不是质数，指数不能取模 mod - 1 而要模 phi(mod) 。
#endif
#include <cstdio>
#include <cassert>

typedef long long lolong;
const int maxk = 62, mod = 10000007; // 这模数不是质数 woctmd
const int phi = 9988440; // phi of mod
lolong C[maxk][maxk];
int tot[maxk];

lolong power(lolong x, int k) {
	assert(k >= 0);
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	lolong n;
	scanf("%lld", &n);
	for(int i = 0; i < maxk; i ++) {
		C[i][0] = 1;
		for(int j = 1; j <= i; j ++)
			// C 出现在指数
			C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % phi;
	}
	int now = 0;
	for(int k = maxk - 1; k >= 0; k --)
		if(n >> k & 1) {
			for(int m = 0; m <= k; m ++)
				(tot[m + now] += C[k][m]) %= phi; // tot 是指数
			now ++;
		}
	tot[now] ++;
	lolong ans = 1;
	for(int k = 1; k < maxk; k ++)
		(ans *= power(k, tot[k])) %= mod;
	printf("%lld\n", ans);
}
