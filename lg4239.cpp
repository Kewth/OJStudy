#pragma GCC optimize(3)
#if 0
2019.04.20

三模数 NTT + 多项式求逆。
然而三模数 NTT 是不能有负数的，否则 x = a (mod p) 即使 p 很大 x = a 也不会成立。
必须在出现负数的地方把绝对值 crt 出来再转负。
也是醉了 A * B^2 会爆模数乘积，需要一次一次卷积。
#endif
#include <bits/stdc++.h>

typedef long long lolong;

lolong power(lolong x, int k, int mod) {
    if(k < 0) k += mod - 1;
    lolong res = 1;
    while(k) {
        if(k & 1) (res *= x) %= mod;
        (x *= x) %= mod;
        k >>= 1;
    }
    return res;
}

const int maxn = 400050;
const int mod[3] = {998244353, 1004535809, 469762049}, Mod = 1000000007;
const __int128 P = __int128(1) * mod[0] * mod[1] * mod[2];
lolong f[maxn], g[maxn];
lolong ff[3][maxn], gg[3][maxn];
int ra[maxn];
__int128 B[maxn];

inline void NTT(lolong *a, const int logn, const int type, int mo) {
    const int n = 1 << logn;
    for(int i = 0; i < n; i ++)
        if(i < ra[i])
            std::swap(a[i], a[ra[i]]);
    for(int m = 2; m <= n; m <<= 1) {
        lolong Gn = power(3, (mo - 1) / m * type, mo);
        for(int i = 0; i < n; i += m) {
            lolong G = 1;
            for(int k = i; k < i + (m >> 1); k ++) {
                lolong a0 = a[k], a1 = a[k + (m >> 1)] * G % mo;
                a[k] = (a0 + a1) % mo;
                a[k + (m >> 1)] = (a0 - a1 + mo) % mo;
                (G *= Gn) %= mo;
            }
        }
    }
    if(type == -1) {
		lolong pp = power(n, -1, mo); // 卡常，这是复杂度瓶颈之一，不然会 T
        for(int i = 0; i < n; i ++)
            (a[i] *= pp) %= mo;
	}
}

inline lolong crt(lolong a, lolong b, lolong c, int p) {
    __int128 res = 0;
    lolong s[6] = {a, b, c};
    for(int i = 0; i < 3; i ++)
		res += B[i] * s[i];
	res %= P;
	/* assert(res % mo[0] == s[0]); */
	/* assert(res % mo[1] == s[1]); */
	/* assert(res % mo[2] == s[2]); */
	/* assert(res < P); */
    return lolong(res % p);
}

void get_inv(const lolong *A, lolong *b, int loglen) {
	if(not loglen) {
		/* b[0] = power(A[0], -1, mod[0]); */
		b[0] = power(A[0], -1, Mod);
		return;
	}
	const int n = 1 << loglen, N = n << 1;
	lolong *inv = new lolong[unsigned(N)], *a = new lolong[unsigned(N)];
	for(int i = 0; i < N; i ++)
		inv[i] = 0;
	get_inv(A, inv, loglen - 1);
	for(int i = 0; i < n; i ++)
		a[i] = A[i];
	for(int i = n; i < N; i ++)
		a[i] = 0;
	for(int i = 0; i < N; i ++) {
		ff[0][i] = ff[1][i] = ff[2][i] = inv[i];
		gg[0][i] = gg[1][i] = gg[2][i] = a[i];
	}
    ra[0] = 0;
    for(int i = 1; i < N; i ++)
        ra[i] = ra[i >> 1] >> 1 | (i & 1) << loglen;
	for(int k = 0; k < 3; k ++) {
		NTT(ff[k], loglen + 1, 1, mod[k]);
		NTT(gg[k], loglen + 1, 1, mod[k]);
		for(int i = 0; i < N; i ++)
			(gg[k][i] *= ff[k][i] % mod[k]) %= mod[k];
		NTT(gg[k], loglen + 1, -1, mod[k]);
	}
	for(int i = 0; i < n; i ++)
		b[i] = crt(gg[0][i], gg[1][i], gg[2][i], Mod);
	for(int i = 0; i < N; i ++)
		gg[0][i] = gg[1][i] = gg[2][i] = b[i];
	for(int k = 0; k < 3; k ++) {
		NTT(gg[k], loglen + 1, 1, mod[k]);
		for(int i = 0; i < N; i ++)
			(gg[k][i] *= ff[k][i] % mod[k]) %= mod[k];
		NTT(gg[k], loglen + 1, -1, mod[k]);
	}
	for(int i = 0; i < n; i ++)
		b[i] = crt(gg[0][i], gg[1][i], gg[2][i], Mod);
	for(int i = 0; i < n; i ++) {
		b[i] = (Mod + inv[i] * 2
			- crt(gg[0][i], gg[1][i], gg[2][i], Mod)) % Mod;
	}
	/* for(int k = 0; k < 3; k ++) { */
	/* 	for(int i = 0; i < n; i ++) */
	/* 		gg[k][i] = (2 * ff[k][i] - gg[k][i] + mod[k]) % mod[k]; */
	/* } */
	/* for(int i = 0; i < n; i ++) { */
	/* 	/1* b[i] = gg[0][i]; *1/ */
	/* 	b[i] = crt(gg[0][i], gg[1][i], gg[2][i], Mod); */
	/* } */
	for(int i = n; i < N; i ++)
		b[i] = 0;
	delete[] inv;
	delete[] a;
}

int main() {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	for(int i = 0; i < n; i ++)
		std::cin >> f[i];
	int loglen = 0;
	while((1 << loglen) < n)
		loglen ++;
    lolong mo[6] = {mod[0], mod[1], mod[2], mod[0], mod[1], mod[2]};
    for(int i = 0; i < 3; i ++)
        B[i] = __int128(mo[i + 1]) * mo[i + 2] % P
            * power(mo[i + 1] * mo[i + 2] % mo[i], -1, int(mo[i])) % P;
	get_inv(f, g, loglen);
	for(int i = 0; i < n; i ++)
		std::cout << g[i] << ' ';
	std::cout << std::endl;
	return 0;
}
