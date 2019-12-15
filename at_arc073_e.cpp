#if 0
2019.12.13

不妨设二元组 (x, y) 满足 x <= y 。

若最大值和最小值颜色不同，贪心构造，
对于剩下的每个 (x, y) ，把 x 放在最小值，y 放在最大值。

否则最大值和最小值颜色相同，那么该颜色的极值确定，需要最小化另一颜色的极值。
依然考虑贪心，在剩下的二元组中每次选出 x 最小的二元组，
如果 x 需要放在新颜色，那么剩下的二元组都把 x 放在新颜色。
否则 y 放在新颜色，更新新颜色的 min, max ，删掉该二元组继续考虑。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> Par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
Par p[maxn];

int main() {
	int n = read;

	for(int i = 1; i <= n; i ++) {
		read(p[i].first, p[i].second);
		if(p[i].first > p[i].second)
			std::swap(p[i].first, p[i].second);
	}

	std::sort(p + 1, p + n + 1);

	int max = 0, min = 1000000000;
	for(int i = 1; i <= n; i ++) {
		max = std::max(max, p[i].second);
		min = std::min(min, p[i].second);
	}

	ll ans = 1ll * (p[n].first - p[1].first) * (max - min);
	debug("%lld\n", ans);

	int mp = 2;
	for(int i = 3; i <= n; i ++)
		if(p[i].second > p[mp].second)
			mp = i;

	for(int i = mp; i >= 3; i --)
		std::swap(p[i], p[i - 1]);

	min = std::min(p[1].second, p[2].first);
	max = std::max(p[1].second, p[2].first);

	int rmin = 1000000000;
	for(int i = 3; i <= n; i ++) {
		rmin = std::min(rmin, std::max(max, p[n].first) - std::min(min, p[i].first));
		min = std::min(min, p[i].second);
		max = std::max(max, p[i].second);
	}
	rmin = std::min(rmin, max - min);

	ans = std::min(ans, 1ll * (p[2].second - p[1].first) * rmin);

	printf("%lld\n", ans);
}
