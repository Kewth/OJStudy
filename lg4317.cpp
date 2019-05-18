#if 0
2019.03.12

对于每个 k 统计 sum(x) == k 的个数即可，
记这个个数是 tot(k) , 那 k 对答案的贡献就是 k^tot(k) ，
统计的方法枚举 n 的每位，以类似数位 DP 的思路去统计。
注意 tot 出现在答案的指数，不能取模（其实可以取模，见 lg4317_2.cpp）
#endif
#include <bits/stdc++.h>

typedef long long lolong;
const int maxk = 52, mod = 10000007;
lolong C[maxk][maxk];
lolong tot[maxk];

lolong power(lolong x, lolong k) {
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

void get_tot(lolong n) {
	unsigned have = 0;
	for(unsigned k = maxk - 1; k < maxk; k --)
		if(n >> k & 1) {
			for(unsigned i = 0; i <= k; i ++)
				tot[have + i] += C[k][i];
			have ++;
		}
	tot[have] ++;
}

int main() {
	lolong n;
	std::cin >> n;
	for(int i = 0; i < maxk; i ++)
		C[i][0] = 1;
	for(int i = 1; i < maxk; i ++)
		for(int j = 1; j <= i; j ++)
			C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
	get_tot(n);
	lolong ans = 1;
	/* for(unsigned k = 1; k < maxk; k ++) */
	/* 	std::clog << tot[k] << std::endl; */
	for(unsigned k = 1; k < maxk; k ++)
		(ans *= power(k, tot[k])) %= mod;
	std::cout << ans << std::endl;
}
