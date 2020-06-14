/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.14

 * Solution:
 * 分离算贡献，贪心

  显然每个点可以用二元组 (id, dis) 表示，其中 id, dis 分别表示该点所属的射线和该点到原点
的距离，可以发现如果选择的点的 id 两两不同，一组选 m 个点的方案的收益就是 dis 乘 (m - 1)
的和，因为每对点的贡献都是 dis1 + dis2 。

  但是注意到如果一对点在一条射线上，其贡献为 |dis1 - dis2| ，即 dis1 + dis2 - min(dis1,
dis2) ，那么每个点在一组方案中的贡献因修正为 (m - 1) * dis - 2k * dis ，其中 k 是该点所
属射线上选取的 dis 比该点大的点数。

  不妨单独考虑每条射线上的点，假设在其中选 k 个点。若 m - 1 - 2k >= 0 ，每个点的贡献都是
正数，显然按 dis 从大到小选最优。若 m - 1 - 2k < 0 ，有一部分的点的贡献为负，那么显然是
对于贡献为正数的部分按 dis 从大到小选，贡献为负数的部分按 dis 从小到大选。于是可以发现，
每个点的贡献实际上是固定的，因为选 k + 1 个点的最优点集严格包含了选 k 个点的最优点集。

  预处理所有点的实际贡献，选最大的 m 个即可。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <cmath>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef double ld;
typedef std::pair<ld, ll> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 500005;
par p[maxn];
ld s[maxn];
bool use[maxn];

int gcd (int a, int b) {
	if (!b) return a;
	return gcd(b, a % b);
}

int main () {
	int n = read, m = read, L = 1000000000;
	std::map<ll, int> map;
	std::map<ll, ld> shit;
	for (int i = 1; i <= n; i ++) {
		int x = read, y = read;
		ld d = std::sqrt(1ll * x * x + 1ll * y * y);
		if (x == 0 and y != 0)
			y = y > 0 ? 1 : -1;
		if (x != 0 and y == 0)
			x = x > 0 ? 1 : -1;
		if (x and y) {
			int g = gcd(std::abs(x), std::abs(y));
			x /= g;
			y /= g;
		}
		ll c = ll(L + x) * (L + L) + (L + y);
		p[i] = par(d, c);
		/* debug("%d %d\n", x, y); */
	}

	std::sort(p + 1, p + n + 1);
	for (int i = n; i; i --) {
		int &k = map[p[i].second];
		if (k * 2 < m - 1) {
			use[i] = 1;
			s[i] = p[i].first * (m - 1) - k * 2 * p[i].first;
			++ k;
		}
		/* ++ map[p[i].second]; */
		/* debug("%lld %lld %lf\n", */
		/* 		p[i].second / (L + L) - L, p[i].second % (L + L) - L, s[i]); */
	}

	for (int i = 1; i <= n; i ++)
		if (!use[i]) {
			int k = map[p[i].second];
			s[i] = p[i].first * (m - 1) - k * 2 * p[i].first - shit[p[i].second];
			shit[p[i].second] += p[i].first * 2;
		}

	std::sort(s + 1, s + n + 1);
	ld ans = 0;
	for (int i = 0; i < m; i ++)
		ans += s[n - i];
	printf("%.8lf\n", ans);
}
