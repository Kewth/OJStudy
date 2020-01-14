#if 0
2020.01.13

枚举右端点，其对应 gcd 不同的左端只有 O(logMAX) 个，
仅保留每个 gcd 距离最远的点，在右端点右移的同时维护一下即可。
#endif
#include <cstdio>
#include <algorithm>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator ()(a...); } */
} read;

inline bool chkmax(int &x, int y) {
	if(y > x) return x = y, 1;
	return 0;
}

inline bool chkmax(ll &x, ll y) {
	if(y > x) return x = y, 1;
	return 0;
}

int main() {
	std::map<ll, int> gcds;
	int n = read;
	ll ans = 0;
	while(n --) {
		ll x = read;
		std::map<ll, int> swap;
		swap[x] = 1;
		chkmax(ans, x);
		for(auto pr : gcds) {
			ll g = std::__gcd(pr.first, x);
			chkmax(swap[g], pr.second + 1);
			chkmax(ans, g * (pr.second + 1));
		}
		gcds = swap;
	}
	printf("%lld\n", ans);
}
