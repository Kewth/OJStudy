#if 0
2020.04.27

  在线分块，把答案分零散到零散，零散到整块，整块到整块三个部分。零散到零散可以直接暴力，
零散到整块只需预处理块的桶也可以暴力，整块到整块可以预处理。
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	/* template<class T> inline void operator () (T &x) { x = *this; } */
} read;

const int maxn = 1 << 17, maxb = 400;
int a[maxn];
int t[maxb][maxn];
int tmp[maxn];
ll f[maxb][maxb];

ll force (int l, int r, int *Ta, int *Tb, int k) {
	ll res = 0;
	for (int i = l; i <= r; i ++)
		res += Ta[k ^ a[i]] - (Tb ? Tb[k ^ a[i]] : 0);
	return res;
}

void push (int l, int r, int x) {
	for (int i = l; i <= r; i ++)
		tmp[a[i]] += x;
}

int main () {
	int n = read, q = read, K = read;
	for (int i = 1; i <= n; i ++) a[i] = a[i - 1] ^ read;
	int B = int(sqrt(n));
	int S = n / B + 1;

	for (int i = 0; i < S; i ++) {
		if (i) std::copy(t[i - 1], t[i - 1] + maxn, t[i]);
		for (int j = 0; j < B; j ++)
			++ t[i][a[i * B + j]];
	}

	for (int l = S - 1; l >= 0; l --) {
		f[l][l] = force(l * B, l * B + B - 1, t[l], l ? t[l - 1] : nullptr, K);
		for (int r = l + 1; r < S; r ++)
			f[l][r] = f[l][r - 1] + f[r][r] +
				(force(r * B, r * B + B - 1, t[r - 1], l ? t[l - 1] : nullptr, K) << 1);
	}

	ll ans = 0;
	while (q --) {
		int l = read - 1, r = read;
		int k = K;
		/* if (O) l ^= ans, r ^= ans, k ^= ans; */
		ans = 0;
		if (l / B == r / B) {
			push(l, r, 1);
			ans += force(l, r, tmp, nullptr, k);
			push(l, r, -1);
		}
		else {
			int lb = l / B, rb = r / B;
			int lR = lb * B + B - 1, rL = rb * B;
			push(l, lR, 1);
			push(rL, r, 1);
			ans += force(l, lR, tmp, nullptr, k);
			ans += force(rL, r, tmp, nullptr, k);
			ans += force(l, lR, t[rb - 1], t[lb], k) << 1;
			ans += force(rL, r, t[rb - 1], t[lb], k) << 1;
			ans += f[lb + 1][rb - 1];
			push(l, lR, -1);
			push(rL, r, -1);
		}
		if (k == 0) ans -= r - l + 1;
		ans >>= 1;
		printf("%lld\n", ans);
	}
}
