#if 0
2019.04.20

三模数 NTT 模板。
CRT 里面不能直接模给定的 p, 而是要先模方程组的模数 (mod0 * mod1 * mod2) ，
但是这个模数巨大，足以爆 long long ，不会奇技淫巧，无脑 __int128 。
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

void NTT(lolong *a, const int logn, const int type, int mod) {
    const int n = 1 << logn;
    int *ra = new int[unsigned(n)];
    ra[0] = 0;
    for(int i = 1; i < n; i ++)
        ra[i] = ra[i >> 1] >> 1 | (i & 1) << (logn - 1);
    for(int i = 0; i < n; i ++)
        if(i < ra[i])
            std::swap(a[i], a[ra[i]]);
    for(int m = 2; m <= n; m <<= 1) {
        lolong Gn = power(3, (mod - 1) / m * type, mod);
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
            (a[i] *= power(n, -1, mod)) %= mod;
    delete[] ra;
}

const int maxn = 400050;
lolong f[maxn], g[maxn];
lolong ff[3][maxn], gg[3][maxn];
const int mod[3] = {998244353, 1004535809, 469762049};

lolong crt(lolong a, lolong b, lolong c, int p) {
    __int128 res = 0, P = 1;
    P = P * mod[0] * mod[1] * mod[2];
    lolong s[6] = {a, b, c, a, b, c};
    lolong mo[6] = {mod[0], mod[1], mod[2], mod[0], mod[1], mod[2]};
    for(int i = 0; i < 3; i ++) {
        res += mo[i + 1] * mo[i + 2] % P
            * power(mo[i + 1] * mo[i + 2] % mo[i], -1, int(mo[i])) % P
            * s[i] % P;
        if(res >= P)
            res -= P;
#if 0
        std::cerr << mo[i + 1] * mo[i + 2] % mo[i]
            * power(mo[i + 1] * mo[i + 2] % mo[i], -1, int(mo[i])) % mo[i]
            * s[i] % mo[i] << ' '
            << mo[i + 1] * mo[i + 2] % mo[i + 1]
            * power(mo[i + 1] * mo[i + 2] % mo[i], -1, int(mo[i])) % mo[i + 1]
            * s[i] % mo[i + 1] << ' '
            << mo[i + 1] * mo[i + 2] % mo[i + 2]
            * power(mo[i + 1] * mo[i + 2] % mo[i], -1, int(mo[i])) % mo[i + 2]
            * s[i] % mo[i + 2] << std::endl;
#endif
    }
    return lolong(res % p);
}

int main() {
    int n, m, p;
    std::cin >> n >> m >> p;
    n ++;
    m ++;
    for(int i = 0; i < n; i ++)
        std::cin >> f[i];
    for(int i = 0; i < m; i ++)
        std::cin >> g[i];
    int loglen = 0;
    while((1 << loglen) < n + m - 1)
        loglen ++;
    for(int k = 0; k < 3; k ++) {
        for(int i = 0; i < n; i ++)
            ff[k][i] = f[i];
        for(int i = 0; i < m; i ++)
            gg[k][i] = g[i];
        NTT(ff[k], loglen, 1, mod[k]);
        NTT(gg[k], loglen, 1, mod[k]);
        for(int i = 0; i < (1 << loglen); i ++)
            (ff[k][i] *= gg[k][i]) %= mod[k];
        NTT(ff[k], loglen, -1, mod[k]);
    }
    /* for(int k = 0; k < 3; k ++) { */
    /* 	for(int i = 0; i < (1 << loglen); i ++) */
    /* 		std::cerr << ff[k][i] << ' '; */
    /* 	std::cerr << std::endl; */
    /* } */
    for(int i = 0; i < n + m - 1; i ++)
        std::cout << crt(ff[0][i], ff[1][i], ff[2][i], p) << ' ';
    std::cout << std::endl;
}
