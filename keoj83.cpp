#if 0
2019.10.10

神奇贪心，求 hack 。
首先 a[i] < b[i] 的一定比 a[i] > b[i] 先选，不选白不选。
那么分成了 a[i] < b[i] 和 a[i] > b[i] 两个部分，
分别考虑两个部分，
直接丢结论，
前面的按 a[i] 递增，后面的按 b[i] 递减。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005;
int a[maxn], b[maxn];
int p[maxn];

bool cmp(int x, int y) {
	if((a[x] < b[x]) == (a[y] < b[y]))
		return a[x] < b[x] ? a[x] < a[y] : b[x] > b[y];
	return (a[x] < b[x]) > (a[y] < b[y]);
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++) {
		a[i] = input();
		b[i] = input();
		p[i] = i;
	}

	std::sort(p + 1, p + n + 1, cmp);

	lolong ans = 0, now = 0;
	for(int i = 1; i <= n; i ++) {
		/* debug("%d %d\n", a[p[i]], b[p[i]]); */
		now -= a[p[i]];
		if(now < 0) {
			ans -= now;
			now = 0;
		}
		now += b[p[i]];
	}

	printf("%lld\n", ans);
}
