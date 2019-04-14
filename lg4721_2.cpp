#if 0
2019.04.14

分治 NTT 模板，就是 cdq 分治？
计算 f 时分治，算出 l-(mid-1) 后再算 l-(mid-1) 的 f 对右边的 f 的贡献，
得出 f[mid] （相当于右边的 f[0]），分治算右边自己对自己的贡献。
需要注意的是要先把左边的贡献加上再去算右边的值。
#endif

#include <bits/stdc++.h>

typedef long long lolong;
const int maxn = 400050, mod = 998244353;

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

void NTT(lolong *a, const int logn, const int type) {
	const int n = 1 << logn;
	int *ra = new int[unsigned(n)];
	ra[0] = 0;
	for(int i = 1; i < n; i ++)
		ra[i] = ra[i >> 1] >> 1 | (i & 1) << (logn - 1);
	for(int i = 0; i < n; i ++)
		if(i < ra[i])
			std::swap(a[i], a[ra[i]]);
	for(int m = 2; m <= n; m <<= 1) {
		lolong Gn = power(3, (mod - 1) / m * type);
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
	delete[] ra;
}

void fuck(lolong *a, lolong *g, const int logn) {
	if(not logn) return;
	fuck(a, g, logn - 1);
	const int n = 1 << logn, mid = n >> 1;
	lolong *b = new lolong [unsigned(n << 1)];
	for(int i = 0; i < mid; i ++)
		b[i] = a[i];
	for(int i = mid; i < (n << 1); i ++)
		b[i] = 0;
	NTT(b, logn + 1, 1);
	NTT(g, logn + 1, 1);
	for(int i = 0; i < (n << 1); i ++)
		(b[i] *= g[i]) %= mod;
	NTT(b, logn + 1, -1);
	NTT(g, logn + 1, -1);
	for(int i = mid; i < n; i ++)
		(a[i] += b[i]) %= mod;
	fuck(a + mid, g, logn - 1);
	delete[] b;
	/* for(int i = 0; i < n; i ++) */
	/* 	std::cerr << a[i] << ' '; */
	/* std::cerr << std::endl; */
}

lolong f[maxn], g[maxn];
int main() {
	int n;
	std::cin >> n;
	for(int i = 1; i < n; i ++)
		std::cin >> g[i];
	g[0] = 0;
	int logn = 0;
	while((1 << logn) < n)
		logn ++;
	f[0] = 1;
	fuck(f, g, logn);
	for(int i = 0; i < n; i ++)
		std::cout << f[i] << ' ';
	std::cout << std::endl;
}
