#if 0
2020.04.09

设 f[i] 表示满足 [f[i] + 1, i] 是合法区间的最大 f[i] 。
事实上 f[i] 可以看做连边 i -> f[i] ，那么求 f[i] 也只需要从 i - 1 开始一直跳边。
但是暴力跳边的复杂度不对，需要用 map 直接存下从每个点开始能跳到的位置。
然后设 g[i] 表示从 i 开始跳几次可以跳出范围，那么 g[i] 的和就是答案。
#endif
#include <cstdio>
#include <algorithm>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 300005;
int a[maxn];
int f[maxn], g[maxn];
std::map<int, int> las[maxn];

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++)
			read(a[i]);
		f[0] = -1;
		ll ans = 0;
		for (int i = 1; i <= n; i ++)
			las[i].clear();
		for (int i = 1; i <= n; i ++) {
			int j = las[i - 1].count(a[i]) ? las[i - 1][a[i]] : -1;
			/* debug("%d %d\n", i, j); */
			/* while (j != -1 and a[i] != a[j]) j = f[j]; */
			f[i] = j == -1 ? j : j - 1;
			g[i] = f[i] == -1 ? 0 : g[f[i]] + 1;
			if (f[i] != -1) las[i].swap(las[f[i]]);
			las[i][a[i]] = i;
			ans += g[i];
		}
		printf("%lld\n", ans);
	}
}
