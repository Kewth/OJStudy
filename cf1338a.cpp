#if 0
2020.04.14

把每个极大的不降子段看做整体，然后从左到右贪心去填即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005;
int a[maxn];

int hb (int x) {
	if (!x) return 0;
	return 32 - __builtin_clz(unsigned(x));
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++) read(a[i]);
		int ans = 0;
		int las = a[1];
		for (int l = 1, r; l <= n; l = r + 1) {
			r = l;
			while (r < n and a[r + 1] >= a[r]) ++ r;
			/* debug("%d %d %d %d\n", l, r, las - a[l], hb(las - a[l])); */
			ans = std::max(ans, hb(las - a[l]));
			las = std::max(a[r], las);
		}
		printf("%d\n", ans);
	}
}
