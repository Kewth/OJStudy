#if 0
2020.03.27

二进制枚举。
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
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 1000005;
int a[maxn];
int tot[30];

int main () {
	int n = read;
	for (int i = 1; i  <= n; i ++) {
		a[i] = read;
		for (int k = 0; k <  30; k ++)
			if (a[i] >> k & 1)
				++ tot[k];
	}

	ll ans = 0;
	for (int k = 0; k <  30; k ++)
		ans += (1ll << k) * tot[k] * tot[k];
	printf("%lld\n", ans);
}
