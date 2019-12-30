#if 0
2019.12.29

设变量 x 为两者味道的异或和，
那么对于每个 a[i] 有三种选择：给 A / 给 B / 不给，
对应于 x ^= a[i] / x ^= a[i] / x ^= 0 ，
构造 A 满足 A[a[i]] = 2, A[0] = 1 ，
那么所有 A 的异或卷积的第 0 项即为答案。
由于 A 的只有 2 个点有值，做多个稀疏数组的 FWT 即可（不知道这个叫什么），
更一般的情况在其他地方提到过，这里略去。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1 << 20, mod = 998244353;

int power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return int(res);
}

void DWT(int *a, int n) {
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++) {
				int a0 = a[k], a1 = a[k + m];
				a[k] = a0 + a1;
				a[k + m] = a0 - a1;
				if(a[k] >= mod) a[k] -= mod;
				if(a[k + m] < 0) a[k + m] += mod;
			}
}

void IDWT(int *a, int n) {
	DWT(a, n);
	int po = power(n, -1);
	for(int i = 0; i < n; i ++)
		a[i] = 1ll * a[i] * po % mod;
}

int a[maxn];
int tmp[maxn];
int ans[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++) {
		read(a[i]);
		++ tmp[0];
		++ tmp[a[i]];
		++ tmp[a[i]];
	}

	DWT(tmp, 1 << 20);

	int inv4 = power(4, -1);
	for(int S = 0; S < (1 << 20); S ++) {
		int x = 1ll * (n + tmp[S]) * inv4 % mod;
		int y = n - x < 0 ? n - x + mod : n - x;
		ans[S] = 1ll * power(3, x) * power(mod - 1, y) % mod;
	}

	IDWT(ans, 1 << 20);
	printf("%d\n", ans[0] ? ans[0] - 1 : mod - 1);
}
