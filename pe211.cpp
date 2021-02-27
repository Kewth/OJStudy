/*
 * Author: Kewth

 * Date:
  2021.01.16

 * Solution:
  预处理 sigma[i] ，然后计算 f[i] 表示和 sigma[i] 最近的平方数与它的距离。然后问题
就变成了二维数点。

 * Digression:
  感觉 HackerRank 的难度评级很迷惑啊。。

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;
typedef std::pair<ll, int> par2;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 6000005;
int minp[maxn];
ll pval[maxn];
ll sigma[maxn], dis[maxn];
std::vector<par> quer[maxn];
par2 tmp[maxn];
ll ans[100005];
ll bit[1000005];

int main () {
	int q = read, N = 0, K = 0;
	for (int i = 1; i <= q; i ++) {
		int n = read, k = read;
		quer[n].push_back(par(k, i));
		N = std::max(N, n);
		K = std::max(K, k);
	}

	sigma[1] = minp[1] = pval[1] = 1;
	tmp[1] = par2(1, 1);
	for (int i = 2; i <= N; i ++) {
		int &p = minp[i];
		if (!p) {
			p = i;
			if (i <= N / i)
				for (int j = i * i; j <= N; j += i)
					if (!minp[j])
						minp[j] = i;
		}
		ll las = minp[i / p] == p ? pval[i / p] : 1;
		pval[i] = las * p * p + 1;
		sigma[i] = sigma[i / p] / las * pval[i];
		tmp[i] = par2(sigma[i], i);
	}

	std::sort(tmp + 1, tmp + N + 1);
	for (int i = 1, x = 1; i <= N; i ++) {
		while (1ll * x * x < tmp[i].first)
			++ x;
		dis[tmp[i].second] = std::min(1ll * x * x - tmp[i].first,
				tmp[i].first - 1ll * (x - 1) * (x - 1));
	}

	for (int i = 1; i <= N; i ++) {
		/* debug("%lld %lld\n", sigma[i], dis[i]); */
		if (dis[i] <= K)
			for (int k = int(dis[i]) + 1; k <= K + 1; k += k & -k)
				bit[k] += i;
		for (par p : quer[i])
			for (int k = p.first + 1; k; k -= k & -k)
				ans[p.second] += bit[k];
	}

	for (int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
}
