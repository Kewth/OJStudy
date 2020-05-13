#if 0
2020.05.12

  单独考虑每个质数的贡献，也就是对指数求最大值对的最小值，也就是次小值。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
int minp[maxn];
std::vector<int> pv[maxn];

int main () {
	int N = 200000;
	minp[1] = 1;
	for (int i = 2; i <= N; i ++) {
		if (!minp[i]) {
			for (int j = i; j <= N; j += i)
				if (!minp[j])
					minp[j] = i;
		}
	}

	int n = read;
	for (int i = 1; i <= n; i ++) {
		int x = read;
		while (x > 1) {
			int p = minp[x], k = 0;
			while (x % p == 0)
				x /= p, ++ k;
			pv[p].push_back(k);
		}
	}

	ll ans = 1;
	for (int i = 1; i <= N; i ++)
		if (minp[i] == i and int(pv[i].size()) >= n - 1) {
			if (int(pv[i].size()) == n - 1)
				pv[i].push_back(0);
			std::sort(pv[i].begin(), pv[i].end());
			int k = pv[i][1];
			while (k --) ans *= i;
		}

	printf("%lld\n", ans);
}
