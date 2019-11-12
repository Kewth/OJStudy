#if 0
2019.11.11

构造完全积性函数 f(x) = x ，用 min25 筛出它在质数上的取值即可。
#endif
#include <cstdio>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxs = 1000010;
ld g[maxs];
ll w[maxs];
ll ph[maxs];
int prime[maxs], pp;
bool nop[maxs];

ll n;
int m, s;
inline int id(ll x) {
	return x <= s ? int(x) : m - int(n / x) + 1;
}

ld solve(ll x) {
	if(!x) return 0;

	n = x;
	s = int(sqrt(n));
	m = 0;

	for(ll l = 1, r; l <= n; l = r + 1) {
		w[++ m] = r = n / (n / l);
		g[m] = w[m] * ld(w[m] + 1) / 2 - 1;
	}

	for(int i = 1; prime[i] <= s; i ++) {
		for(int j = m; j and prime[i] <= w[j] / prime[i]; j --)
			g[j] -= prime[i] * (g[id(w[j] / prime[i])] - ph[i - 1]);
		/* for(int j = 1; j <= m; j ++) */
		/* 	debug(" %.0Lf", g[j]); */
		/* debug("\n"); */
	}

	return g[m];
}

int main() {
	s = 1000000;

	for(int i = 2; i <= s; i ++) {
		if(!nop[i]) {
			prime[++ pp] = i;
			ph[pp] = ph[pp - 1] + i;
		}
		for(int j = 1; j <= pp; j ++) {
			if(prime[j] > s / i) break;
			nop[i * prime[j]] = 1;
			if(!(i % prime[j])) break;
		}
	}

	ll l = read, r = read;
	printf("%.0Lf\n", solve(r) - solve(l - 1));
}
