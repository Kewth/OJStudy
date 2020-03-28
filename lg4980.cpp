#if 0
2019.03.18

我 Naive 了
一开始对 polya 定理有误解，把这当成了傻逼题直接打了后调都没调就交。

这题用 polya 推一推式子，式子上面的那个指数就是 gcd(n, k) ，直接做是 n log 的。
看式子嘛，有个 gcd(n, k) 那就枚举 g = gcd(n, k) ，提到前面，加个互质条件，
互质条件转换为莫比乌斯函数，把 d 也往前提，
然后提出了一个莫比乌斯函数和单位函数的卷积，就是欧拉函数啦。
然后暴力求出那些欧拉函数（ n 太大了不能筛）

卧槽这怎么变成了一道数论题

emm 然而还是 Naive, 我发现我不会暴力求 phi, 抄了份代码才读懂。
#endif
#include <bits/stdc++.h>

typedef long long lolong;
const int mod = 1000000007;

lolong power(lolong x, int k) {
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int phi(int n) {
	int res = 1;
	for(int i = 2; i * i <= n; i ++)
		if(n % i == 0) { // i 一定是质数
			res *= i - 1; // phi(i) = i - 1
			n /= i;
			while(n % i == 0) {
				res *= i;
				n /= i;
			}
		}
	if(n > 1)
		res *= n - 1;
	/* std::clog << "phi " << n << " = " << res << std::endl; */
	return res;
}

int main() {
	int T;
	std::cin >> T;
	while(T --) {
		int n;
		std::cin >> n;
		int ans = 0;
		for(int g = 1; g * g <= n; g ++)
			if(n % g == 0) {
				ans += power(n, n / g - 1) * phi(g) % mod;
				if(ans >= mod) ans -= mod; // 不加会爆
				if(g * g < n)
					ans += power(n, g - 1) * phi(n / g) % mod;
				if(ans >= mod) ans -= mod;
			}
		std::cout << ans << std::endl;
	}
}
