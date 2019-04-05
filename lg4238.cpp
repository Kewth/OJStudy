#if 0
2019.04.05

多项式求逆模板。
在多项式相乘的长度这方面卡了好久。
然后又在函数传指针这块卡了好久（论不控制变量作用域的危害）。
#endif
#include <bits/stdc++.h>

typedef long long lolong;
const int maxn = 400050, mod = 998244353;
lolong f[maxn], g[maxn];
int ra[maxn];

lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

void NTT(lolong *a, int n, int type) {
	for(int i = 0; i < n; i ++)
		if(i < ra[i])
			std::swap(a[i], a[ra[i]]);
	for(int m = 2; m <= n; m <<= 1) {
		lolong Gn = power(3, type * (mod - 1) / m);
		for(int i = 0; i < n; i += m) {
			lolong G = 1;
			for(int k = i; k < i + (m >> 1); k ++) {
				lolong a0 = a[k], a1 = a[k + (m >> 1)] * G % mod;
				a[k] = (a0 + a1) % mod;
				a[k + (m >> 1)] = (a0 - a1 + mod) % mod;
				(G *= Gn) %= mod;
			}
		}
	}
	if(type == -1)
		for(int i = 0; i < n; i ++)
			(a[i] *= power(n, -1)) %= mod;
}

void get_inv(const lolong *A, lolong *b, int n) {
	if(n == 1) {
		b[0] = power(A[0], -1);
		return;
	}
	const int N = n << 1;
	lolong *inv = new lolong[unsigned(N)], *a = new lolong[unsigned(N)];
	for(int i = 0; i < N; i ++)
		inv[i] = 0;
	for(int i = 0; i < n; i ++)
		a[i] = A[i];
	for(int i = n; i < N; i ++)
		a[i] = 0;
	get_inv(A, inv, n >> 1);
	int logn = 0;
	while(1 << logn < N)
		logn ++;
	for(int i = 1; i < N; i ++)
		ra[i] = ra[i >> 1] >> 1 | (i & 1) << (logn - 1);
	NTT(a, N, 1);
	NTT(inv, N, 1);
	for(int i = 0; i < N; i ++)
		b[i] = a[i] * inv[i] % mod * inv[i] % mod;
	NTT(b, N, -1);
	NTT(inv, N, -1);
	for(int i = 0; i < n; i ++)
		b[i] = ((inv[i] << 1) - b[i] + mod) % mod;
	for(int i = n; i < N; i ++)
		b[i] = 0;
	delete[] inv;
}

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	for(int i = 0; i < n; i ++)
		std::cin >> f[i];
	int len = 1;
	while(len < n)
		len <<= 1;
	get_inv(f, g, len);
	for(int i = 0; i < n; i ++)
		std::cout << g[i] << ' ';
	std::cout << std::endl;
	return 0;
}
