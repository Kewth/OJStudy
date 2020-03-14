#if 0
2020.03.13

预处理出所有连续的必胜点段，容易发现每次段长倍增，段数是 O(logV) 的。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, ll> par;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

std::vector<par> v;

int main() {
	ll x = 2, lim = 1000000000000000000;
	while(x <= lim) {
		v.push_back(par(x, x * 2 - 1));
		x = 4 * x - 1;
	}

	int T = read;
	while(T --) {
		ll n = read;
		bool ans = 0;
		for(par p : v)
			if(p.first <= n and n <= p.second)
				ans = 1;
		if(ans) puts("XiaoHuiHui");
		else puts("XiaoQiao");
	}
}
