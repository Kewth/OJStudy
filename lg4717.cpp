#if 0
2019.03.04

FWT 位运算三合一模板题。
#endif
#include <bits/stdc++.h>

int input() { int x; scanf("%d", &x); return x; }

typedef long long lolong;
const int maxn = 1 << 20, MOD = 998244353;
const lolong mod = MOD;
lolong a[maxn], b[maxn], c[maxn];

lolong inv(lolong x) {
	switch(x) {
		case -2:
			return -499122177;
		case -1:
			return -1;
		case 1:
			return 1;
		case 2:
			return 499122177;
		default:
			lolong res = 1;
			int k = mod - 2;
			while(k) {
				if(k & 1) (res *= x) %= mod;
				(x *= x) %= mod;
				k >>= 1;
			}
			exit(3);
			return res;
	}
}

void FWT(lolong *x, int n, bool type, int f00, int f01, int f10, int f11) {
	for(int m=2; m<=n; m<<=1)
		for(int k=0; k<n; k+=m)
			for(int i=k; i<k+(m>>1); i++) {
				lolong xl = x[i], xr = x[i + (m >> 1)];
				if(type) {
					x[i] = f00 * xl % mod + f01 * xr % mod;
					x[i + (m >> 1)] = f10 * xl % mod + f11 * xr % mod;
				} else {
					x[i] = f11 * xl % mod - f01 * xr % mod;
					x[i + (m >> 1)] = f10 * xl % mod - f00 * xr % mod;
					x[i] *= inv(f01 * f10 - f00 * f11);
					x[i + (m >> 1)] *= inv(f01 * f10 - f00 * f11);
					x[i] *= -1;
				}
				(x[i] += mod) %= mod;
				(x[i + (m >> 1)] += mod) %= mod;
			}
}

void FWT_or(lolong *x, int n, bool type) {
	FWT(x, n, type, 1, 0, 1, 1);
}

void FWT_and(lolong *x, int n, bool type) {
	FWT(x, n, type, 1, 1, 0, 1);
}

void FWT_xor(lolong *x, int n, bool type) {
	FWT(x, n, type, 1, 1, 1, -1);
}

int main() {
	int l = input(), n = 1 << l;
	for(int i=0; i<n; i++)
		a[i] = input();
	for(int i=0; i<n; i++)
		b[i] = input();
	FWT_or(a, n, true);
	/* for(int i=0; i<n; i++) */
	/* 	fprintf(stderr, "%lld ", a[i] < 0 ? a[i] + mod : a[i]); */
	/* fputs("\n", stderr); */
	FWT_or(b, n, true);
	for(int i=0; i<n; i++)
		c[i] = a[i] * b[i];
	FWT_or(a, n, false);
	FWT_or(b, n, false);
	FWT_or(c, n, false);
	for(int i=0; i<n; i++)
		printf("%lld ", c[i] < 0 ? c[i] + mod : c[i]);
	puts("");
	FWT_and(a, n, true);
	FWT_and(b, n, true);
	for(int i=0; i<n; i++)
		c[i] = a[i] * b[i];
	FWT_and(a, n, false);
	FWT_and(b, n, false);
	FWT_and(c, n, false);
	for(int i=0; i<n; i++)
		printf("%lld ", c[i] < 0 ? c[i] + mod : c[i]);
	puts("");
	FWT_xor(a, n, true);
	FWT_xor(b, n, true);
	for(int i=0; i<n; i++)
		c[i] = a[i] * b[i];
	FWT_xor(a, n, false);
	FWT_xor(b, n, false);
	FWT_xor(c, n, false);
	for(int i=0; i<n; i++)
		c[i] %= MOD;
	for(int i=0; i<n; i++)
		printf("%lld ", c[i] < 0 ? c[i] + MOD : c[i]);
	puts("");
}
