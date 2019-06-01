#if 0
2019.06.01

学到了， O(n) 计算数组逆元。
先处理 a 的前缀积 s ，考虑如何求 s 的逆元 v。
根据 v[i] = 1/s[i] = a[i+1]/s[i+1] = a[i+1]*v[i+1] 可以得到 v 的线性递推。
那么 a[i] 的逆元就是 s[i - 1] * v[i] 。
#endif
#include <cstdio>

typedef long long lolong;
const int maxn = 5000050;
int a[maxn], s[maxn], v[maxn];

int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

lolong power(lolong x, int k, int mod) {
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = input(), p = input(), k = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	s[1] = a[1];
	for(int i = 2; i <= n; i ++)
		s[i] = 1ll * s[i - 1] * a[i] % p;
	v[n] = int(power(s[n], p - 2, p));
	for(int i = n - 1; i; i --)
		v[i] = 1ll * a[i + 1] * v[i + 1] % p;
	a[1] = v[1];
	for(int i = 2; i <= n; i ++)
		a[i] = 1ll * s[i - 1] * v[i] % p;
	lolong ans = 0;
	int m = k;
	for(int i = 1; i <= n; i ++) {
		ans += 1ll * a[i] * m % p;
		m = 1ll * m * k % p;
	}
	printf("%lld\n", ans % p);
}
