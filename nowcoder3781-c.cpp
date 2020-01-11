#if 0
2020.01.10

构造数组 a ，a[S] = 1 当且仅当 S 集合能被一个箱子装下。
那么将 a 做 x 次或卷积得到 b ，b[S] > 0 当且仅当 S 集合能被 x 个箱子装下。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 23;
ll a[1 << maxn];
int w[maxn];
const int magic = 19260817, mod = magic;

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

void FWT(int n, int t) {
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += m << 1)
			for(int k = i; k < i + m; k ++)
				(a[k + m] += mod + a[k] * t) %= mod;
}

int main() {
	int T = read;
	while(T --) {
		int n = read, x = read, W = read;
		for(int i = 0; i < n; i ++)
			read(w[i]);
		for(int S = 0; S < (1 << n); S ++) {
			ll sum = 0;
			for(int i = 0; i < n; i ++)
				if(S >> i & 1)
					sum += w[i];
			a[S] = sum <= W;
		}
		FWT(1 << n, 1);
		for(int S = 0; S < (1 << n); S ++)
			a[S] = power(a[S], x);
		FWT(1 << n, -1);
		if(a[(1 << n) - 1])
			puts("Yes");
		else
			puts("No");
	}
}
