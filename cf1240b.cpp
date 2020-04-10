#if 0
2020.04.09

可以发现向左移动的一定是最小的一段数，向右移动的一定是最大的一段数。
要最大化不移动的数，只需要最大化一段权值区间，满足这些权值的位置单调。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 300005;
int l[maxn], r[maxn];

int main () {
	int T = read;
	while (T --) {
		int n = read;
		std::fill(l, l + n + 1, 0);
		std::fill(r, r + n + 1, 0);

		for (int i = 1; i <= n; i ++) {
			int x = read;
			if (!l[x]) l[x] = i;
			r[x] = i;
		}

		int ans = 0, max = 0;
		for (int x = 1, y = 0, now = 0; x <= n; x ++)
			if (l[x]) {
				if (r[y] < l[x]) ++ now;
				else now = 1;
				++ ans;
				max = std::max(max, now);
				y = x;
			}
		ans -= max;
		printf("%d\n", ans);
	}
}
