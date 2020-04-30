#if 0
2020.04.29

如果第一个数放在了位置 p ，那么就必须一直连续向后填直到碰到已经填的数，据此判定即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
int a[maxn], b[maxn];

bool check (int n, int m) {
	if (!m) return 1;
	int x = n - m + 1;
	int p = b[x];
	for (int i = p; i <= m; i ++)
		if (a[i] != x + i - p)
			return 0;
	return check(n, p - 1);
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++) b[a[i] = read] = i;
		if (check(n, n)) puts("Yes");
		else puts("No");
	}
}
