#if 0
2018.03.27

很不错的一道式子题，同时学了 NTT 和斯特灵数。
把 i, j 的顺序交换一下再把可以移的东西移出第二个 sigma （套路），
然后就是求后面的斯特灵数的求和 g[i] = \sum_j^n S(j, i) ，
根据斯特灵数的转移可以得出 g 的转移：
g[i] = (S(n + 1, i) - g[i - 1]) / (i - 1) ，
NTT 求出一排斯特灵数即可。
#endif
#include <bits/stdc++.h>

typedef long long lolong;
const int maxn = 400050, mod = 998244353;
lolong f[maxn], g[maxn], s[maxn], dp[maxn];
int r[maxn];

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
    for(int i=0; i<n; i++)
        if(i < r[i])
            std::swap(a[i], a[r[i]]);
    for(int m=2; m<=n; m<<=1) { // 区间长
        lolong Gn = power(3, ((mod - 1) / m) * type);
        for(int i=0; i<n; i+=m) { // 起点
            lolong G = 1;
            for(int k=i; k<i+(m>>1); k++) { // 位置
                lolong a0 = a[k], a1 = a[k + (m >> 1)];
                a[k] = (a0 + G * a1) % mod;
                a[k + (m >> 1)] = (a0 + (mod - G) * a1) % mod;
                (G *= Gn) %= mod;
            }
        }
    }
}

int main() {
    int n;
    std::cin >> n;
    int nm = 1, lognm = 0;
    while(nm < (n + 2) << 1) {
        nm <<= 1;
        lognm ++;
    }
    for(int i = 0; i < nm; i ++)
        r[i] = r[i >> 1] >> 1 | (i & 1) << (lognm - 1);
    lolong jie = 1;
    for(int i = 0; i < (nm >> 1); i ++) {
        if(i) (jie *= i) %= mod;
        f[i] = power(mod - 1, i) * power(jie, -1) % mod;
        g[i] = power(i, n + 1) * power(jie, -1) % mod;
    }
	for(int i = 0; i < nm; i ++)
		std::clog << f[i] << ' ';
	std::clog << std::endl;
	for(int i = 0; i < nm; i ++)
		std::clog << g[i] << ' ';
	std::clog << std::endl;
    NTT(f, nm, 1);
    NTT(g, nm, 1);
    for(int i = 0; i < nm; i++)
        s[i] = f[i] * g[i] % mod;
    NTT(s, nm, -1);
    for(int i = 0; i < nm; i ++)
        (s[i] *= power(nm, -1)) %= mod;
    dp[0] = 0;
    dp[1] = n;
    for(int i = 2; i <= n; i ++)
        dp[i] = (mod + s[i] - dp[i - 1]) * power(i - 1, -1) % mod;
    lolong ans = 0;
    jie = 1;
    for(int i = 0; i <= n; i ++) {
        if(i) (jie *= i) %= mod;
        ans += power(2, i) * jie % mod * dp[i] % mod;
    }
    (ans += 1) %= mod;
    std::cout << ans << std::endl;
}
