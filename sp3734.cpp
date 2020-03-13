#if 0
2020.03.11

对 h 序列建笛卡尔树，树上每个节点就实际代表了一个矩形。
在笛卡尔树上 DP ，设 f[u][k] 表示放 k 个点在 u 子树内的矩形中的方案数。
转移先放儿子，再放自己，计算排列组合很容易得出方案。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 505, maxh = 1000005, mod = 1000000007;
int h[maxn];
int ls[maxn], rs[maxn], len[maxn], hei[maxn];
ll f[maxn][maxn];
ll tmp[maxn];
ll fac[maxh], ifac[maxh];

ll C(int n, int m) { return fac[n] * ifac[m] % mod * ifac[n - m] % mod; }

int build(int l, int r, int fa) {
	if(l > r) return 0;
	int rt = r;
	for(int k = l; k < r; k ++)
		if(h[k] < h[rt])
			rt = k;
	ls[rt] = build(l, rt - 1, rt);
	rs[rt] = build(rt + 1, r, rt);
	len[rt] = r - l + 1;
	hei[rt] = h[rt] - h[fa];
	return rt;
}

void dp(int u) {
	if(!u) return;
	int L = ls[u], R = rs[u];
	dp(L);
	dp(R);
	std::fill(tmp, tmp + len[u], 0);
	for(int a = 0; a <= len[L]; a ++)
		for(int b = 0; b <= len[R]; b ++)
			(tmp[a + b] += f[L][a] * f[R][b]) %= mod;
	for(int a = 0; a < len[u]; a ++)
		for(int b = 0; a + b <= len[u] and b <= hei[u]; b ++)
			(f[u][a + b] += tmp[a] * fac[b] % mod *
			 C(len[u] - a, b) % mod * C(hei[u], b)) %= mod;
}

int main() {
	int n = read, k = read;
	for(int i = 1; i <= n; i ++)
		h[i] = read;

	int H = 1000000;
	fac[0] = 1;
	for(int i = 1; i <= H; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[1] = 1;
	for(int i = 2; i <= H; i ++)
		ifac[i] = (mod - mod / i) * ifac[mod % i] % mod;
	ifac[0] = 1;
	for(int i = 1; i <= H; i ++)
		(ifac[i] *= ifac[i - 1]) %= mod;

	int rt = build(1, n, 0);
	f[0][0] = 1;
	dp(rt);
	printf("%lld\n", f[rt][k]);
}
