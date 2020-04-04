#if 0
2020.02.21

先考虑没有修改的情况。
不难发现对于于一个已经投了 x 个奖池，再投一个的期望增量是关于 x 的减函数。
也就是说往同一个奖池投的话收益会逐渐减小，特别的 x >= l 时收益为 0 。
那么用堆维护每个奖池的收益，每次选最大收益的奖池即可。

每次修改，先计算出它对当前已经选择的最优方案的影响。
然后此时的方案可能已经不是最优方案，每次找出当前方案中收益最小的那次操作，
然后在可以选择的奖池中找出收益最大的奖池，
如果替换两者能使收益变大，就一直替换。
同样两边都用堆维护即可，由于修改只会影响一个奖池，
对应地就只会影响两边堆的一个点。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 200005;
int p[maxn], l[maxn], u[maxn];

inline ld calc(int i, int x) {
	x = std::min(x, l[i]);
	if(x == -1) return - 1e100;
	return ld(p[i]) * x / (l[i] + x);
}

struct Pool {
	int i, x;
	ld val;
	Pool (int i, int x): i(i), x(x), val(calc(i, x + 1) - calc(i, x)) { }
	inline Pool dec() { return Pool(i, x - 1); }
	inline Pool inc() { return Pool(i, x + 1); }
};
bool operator < (Pool a, Pool b) {
	return a.val == b.val ? a.i < b.i : a.val < b.val;
}

std::set<Pool> get, wait;
ld ans = 0;
inline void add() {
	Pool P = *(-- wait.end());
	ans += P.val;
	++ u[P.i];
	get.erase(P.dec());
	get.insert(P);
	wait.erase(P);
	wait.insert(P.inc());
}

inline void remove() {
	Pool P = *get.begin();
	ans -= P.val;
	-- u[P.i];
	get.erase(P);
	get.insert(P.dec());
	wait.erase(P.inc());
	wait.insert(P);
}

int main() {
	int n = read, t = read, q = read;
	for(int i = 1; i <= n; i ++)
		p[i] = read;
	for(int i = 1; i <= n; i ++)
		l[i] = read;

	for(int i = 1; i <= n; i ++)
		wait.insert(Pool(i, 0));
	while(t --) add();

	while(q --) {
		int o = read, i = read;

		ans -= calc(i, u[i]);
		get.erase(Pool(i, u[i] - 1));
		wait.erase(Pool(i, u[i]));

		if(o == 1) ++ l[i];
		if(o == 2) -- l[i];

		ans += calc(i, u[i]);
		get.insert(Pool(i, u[i] - 1));
		wait.insert(Pool(i, u[i]));

		while(*get.begin() < *(-- wait.end())) {
			remove();
			add();
		}

		printf("%.7lf\n", double(ans));
	}
}
