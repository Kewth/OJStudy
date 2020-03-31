#if 0
2020.03.31

从小到大枚举答案后检查即可，可以知道答案的上界是 O(logV) 的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

int main () {
	int n = read, p = read, ans = 100000000;
	for (int x = 1; x < 1000000; x ++) {
		ll s = n - 1ll * x * p;
		if (s < x) break;
		int tot = 0;
		for (int k = 0; k < 60; k ++) tot += s >> k & 1;
		if (tot <= x)
			ans = std::min(ans, x);
	}
	printf("%d\n", ans == 100000000 ? -1 : ans);
}
