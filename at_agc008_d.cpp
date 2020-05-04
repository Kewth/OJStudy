#if 0
2020.05.04

贪心按位置从小到大填数即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 505;
int a[maxn * maxn];
par p[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		p[i] = par(read, i);
	std::sort(p + 1, p + n + 1);

	int ap = 0;
	for (int i = 1; i <= n; i ++) {
		int k = p[i].first, x = p[i].second;
		for (int j = 1; j < x; j ++) {
			while (a[ap + 1]) ++ ap;
			a[++ ap] = x;
		}
		if (a[k]) return puts("No"), 0;
		a[k] = x;
	}

	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n - i; j ++) {
			while (a[ap + 1]) ++ ap;
			a[++ ap] = i;
		}
	}

	puts("Yes");
	for (int i = 1; i <= n * n; i ++)
		printf("%d ", a[i]);
	puts("");
}
