/*
 * Author: Kewth

 * Date:
  2020.10.19

 * Solution:
 * 问题转换，传递闭包，SCC 缩点，状压 DP

  首先不难注意到一个 for 循环就是一个形如 l <= i <= r 的不等式，lag 的运行次数实际上是
满足所有不等式的变量组数。

  按不等关系连边，显然 SCC 内的值要相同，缩点得到一张新图 G 。不难想到 n 的指数就是 G
的点数，接下来着重考虑计算渐进复杂度的常数。

  由于渐进复杂度是在 n 趋于正无穷时体现出来的，不妨令 n 为正无穷，那么每个变量的取值范
围就是整个正整数域，不妨钦定 G 内变量的取值是两两不同的，考虑每个变量随机取值，满足所
有限制的概率。事实上这个概率就是我们要计算的系数。

  由于我们只关心变量之间的大小关系，按变量从小到大得到排列 p ，每个排列 p 的出现概率都
是 1 / m! ，其中 m 是 G 的点数。假设合法的排列数量是 k ，那么要计算的系数就是 k / m! 。
于是问题转换为求合法的排列数，也就是拓扑排序的方案数，用状压 DP 可以很好解决。

 * Digression:
  真实菜逼，先是不会算拓扑序数量，再是 Floyd 写错连 WA 两发。

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 20;
int id[26];
bool link[maxn][maxn];
int scc[maxn], scc_tot;
int slink[maxn];
ll f[1 << maxn];

int main () {
	int n = read - 1;
	for (int i = 0; i < n; i ++) {
		char now = '?', left = '?', right = '?';
		scanf("\nfor %c in range(%c, %c):", &now, &left, &right);
		/* debug("%c %c %c\n", now, left, right); */
		id[now - 'a'] = i;
		if (left != '1') link[i][id[left - 'a']] = 1;
		if (right != 'n') link[id[right - 'a']][i] = 1;
	}

	for (int k = 0; k < n; k ++)
		for (int i = 0; i < n; i ++)
			for (int j = 0; j < n; j ++)
				link[i][j] |= link[i][k] & link[k][j];

	for (int i = 0; i < n; i ++)
		scc[i] = -1;
	for (int i = 0; i < n; i ++)
		if (scc[i] == -1) {
			scc[i] = scc_tot ++;
			for (int j = i + 1; j < n; j ++)
				if (link[i][j] and link[j][i])
					scc[j] = scc[i];
		}

	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			if (link[i][j] and scc[i] != scc[j])
				slink[scc[i]] |= 1 << scc[j];

	f[0] = 1;
	for (int S = 1; S < (1 << scc_tot); S ++) {
		for (int i = 0; i < scc_tot; i ++)
			if (S >> i & 1 and (slink[i] & S) == 0)
				f[S] += f[S ^ (1 << i)];
	}

	ll x = f[(1 << scc_tot) - 1], y = 1;
	for (int i = 1; i <= scc_tot; i ++) y *= i;
	ll g = std::__gcd(x, y);
	printf("%d %lld/%lld\n", scc_tot, x / g, y / g);
}
