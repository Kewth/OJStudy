#pragma GCC optimize(3)
#if 0
2020.05.30

  首先各凭本事的博弈归纳（打表找规律）可以知道有 E(n) = 1 + 1/2 + ... + 1/n 。设序列
a(n) = 1/n ，其生成函数为 F_0(x) ，则有 F_0(x) = - ln(1 - x) 。那么 E(n) 就是 a 的前
缀和，其生成函数为 F_1(x) = - ln(1 - x) / (1 - x) ，进一步的，可以知道 S_k(n) 的生成
函数就是 F_{k+1}(x) = - ln(1 - x) / (1 - x)^{k+1} 。
  注意到对于 k = 0 ，可以用 ln(n) + k + 1/2n 来拟合 E(n) ，其中 k 是欧拉常数，而对于
S_k(n) 缺难以直接找到公式拟合，但是可以考虑把 S_k 的计算逐步转换到 E 的计算上来。具
体的，对 F_{k+1}(x) 求导，可以得到 F_{k+1}(x) 的导函数与 F_{k+2}(x) 的关系，照套路比
较多项式等式的各项系数，就能得到 S_k(n+1) 和 S_{k+1}(n) 的关系。那么一步步递推到
k = 0 用公式拟合即可，中间要暴力求一个组合数，复杂度 O(k^2) 。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <cmath>
#include <iostream>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

const ld E = 0.57721566490153286060651209L;

ld C (ll n, int m) {
	ld res = 1;
	for (int i = 1; i <= m; i ++) {
		res *= n - i + 1;
		res /= i;
	}
	return res;
}

ld F (int k, ll n) {
	if (n <= 10000000) {
		ld coe = 1, res = 0;
		for (ll i = 0; i < n; i ++) {
			res += coe / (n - i);
			coe *= k + i + 1;
			coe /= i + 1;
		}
		return res;
	}
	if (k == 0)
		return std::log(ld(n)) + E + ld(1) / (n * 2);
	return ((n + 1) * F(k - 1, n + 1) - C(n + k, k)) / k;
}

int main () {
	std::cout.unsetf(std::ios::fixed);
	std::cout.setf(std::ios::scientific);
	std::cout.precision(9);
	std::cout << F(20, 100000000000000) << std::endl;
}
