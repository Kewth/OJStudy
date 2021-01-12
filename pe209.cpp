/*
 * Author: Kewth

 * Date:
  2021.01.12

 * Solution:
 * 阈值分类，生成树树边非树边分类，容斥，折半搜索

  题目讲了那么多，实际上就是：给定一张 64 点 64 边的图，求独立集的数量。单独考虑每个连通
块，有两个可行算法。

  算法一：搜索点集，朴素的想法是枚举点集判断是否是独立集，复杂度 O(2^n) 。

  用折半搜索优化，把点集分成 AB 两部分，枚举 A 内的所有独立集，dp 预处理 B 内每个点集内
的独立集数量，就可以 O(2^(n/2)) 算出答案。

  算法二：按边容斥，朴素的想法是枚举边集计算其子图的点数，复杂度 O(2^m) 。

  找出一颗生成树，仅仅枚举非树边的子集，对于树边可以树形 DP 计算答案，可做到 O(2^(m-n))

  综上，总复杂度 O(2^(min(n / 2, m - n))) = O(2^(|E|/3)) 。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long ull;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

ull get_func (int N) {
	static char s[1000];
	scanf("%s", s);
	/* int len = int(strlen(s)); */
	ull res = 0;
	for (int x = 0; x < N; x ++) {
		bool _xor = 0, _and = 1;
		for (int i = 0; s[i]; i ++) {
			if (s[i] == 'a')
				_and &= x >> (s[++ i] - '1') & 1;
			else if (s[i] == '0' or s[i] == '1')
				_and &= s[i] - '0';
			else if (s[i] == '+')
				_xor ^= _and, _and = 1;
		}
		_xor ^= _and;
		res |= ull(_xor) << x;
	}
	return res;
}

ull solve1 (int n, ull *link) { // 2^(V/2)
	const int maxm = 23;
	static ull f[1 << maxm], blink[1 << maxm];
	int m = n >> 1;
	if (n > maxm * 2) exit(1);

	f[0] = 1;
	for (ull A = 1; A < (1llu << m); A ++) {
		int i = 0;
		while (!(A >> i & 1)) ++ i;
		f[A] = f[A ^ (1 << i)] + f[(A ^ (1 << i)) & ~link[i]];
	}

	blink[0] = 0;
	for (ull B = 1; B < (1llu << (n - m)); B ++) {
		int i = 0;
		while (!(B >> i & 1)) ++ i;
		blink[B] = blink[B ^ (1 << i)] | link[m + i];
	}

	ull ans = 0;
	for (ull B = 0; B < (1llu << (n - m)); B ++)
		if (!(blink[B] & (B << m))) {
			ull AA = ~blink[B] & ((1llu << m) - 1);
			ans += f[AA];
		}

	return ans;
}

ull dfs_can;
int dfs_lis[64], lp;
bool tree[64][64];
void dfs (int x, ull *link) {
	dfs_lis[lp ++] = x;
	dfs_can ^= 1llu << x;
	for (int i = 0; i < 64; i ++)
		if ((link[x] & dfs_can) >> i & 1)
			tree[x][i] = 1, dfs(i, link);
}

ull solve2 (int n, ull *link) { // 2^(E-V)
	lp = 0;
	dfs_can = ull(-1);
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			tree[i][j] = 0;
	dfs(0, link);
	if (lp != n) debug("ERROR\n");

	int ex[64], ey[64], fa[64], e = 0;
	ull f[64], g[64];

	for (int i = 0; i < n; i ++)
		for (int j = i + 1; j < n; j ++)
			if (!tree[i][j] and !tree[j][i] and link[i] >> j & 1)
				ex[e] = i, ey[e] = j, e ++;

	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			if (tree[i][j])
				fa[j] = i;

	ull ans = 0;
	for (int S = 0; S < (1 << e); S ++) {
		ull now = 1;
		std::fill(f, f + n, 1);
		std::fill(g, g + n, 1);
		for (int i = 0; i < e; i ++)
			if (S >> i & 1)
				now *= ull(-1), g[ex[i]] = g[ey[i]] = 0;
		for (int i = lp - 1; i >= 0; i --) {
			int x = dfs_lis[i];
			if (i) f[fa[x]] *= g[x], g[fa[x]] *= f[x] + g[x];
			/* for (int y = 0; y < n; y ++) */
			/* 	if (tree[x][y]) */
			/* 		f[x] *= g[y], g[x] *= f[y] + g[y]; */
		}
		now *= f[dfs_lis[0]] + g[dfs_lis[0]];
		ans += now;
	}

	return ans;
}

ull solve (ull G, ull *olink) {
	int list[64], n = 0;
	for (int x = 0; x < 64; x ++)
		if (G >> x & 1)
			list[n ++] = x;

	ull link[64];
	std::fill(link, link + n, 0);
	int m = 0;
	for (int i = 0; i < n; i ++)
		for (int j = 0; j < n; j ++)
			if (olink[list[i]] >> list[j] & 1)
				link[i] |= 1llu << j, ++ m;

	/* debug("solve\n"); */
	/* for (int i = 0; i < n; i ++) { */
	/* 	for (int j = 0; j < n; j ++) */
	/* 		debug("%llu", link[i] >> j & 1); */
	/* 	debug("\n"); */
	/* } */

	// 无自环且连通
	if (n == 0) return 1;
	if (n == 1) return 2;
	if (n == 2) return 3;

	if (n / 2 <= n - m + 1)
		return solve1(n, link);
	return solve2(n, link);
}

int main () {
	int T = read;
	while (T --) {
		ull F[6], G[6];
		int n = read, N = 1 << n;
		for (int i = 0; i < n; i ++)
			F[i] = get_func(N);
		for (int i = 0; i < n; i ++)
			G[i] = get_func(N);

		ull link[64];
		std::fill(link, link + N, 0);
		for (int x = 0; x < N; x ++) {
			int a = 0, b = 0;
			for (int i = 0; i < n; i ++) {
				a |= (F[i] >> x & 1) << i;
				b |= (G[i] >> x & 1) << i;
			}
			link[a] |= 1llu << b;
			link[b] |= 1llu << a;
			/* debug("%d %d\n", a, b); */
		}

		ull selflink = 0;
		for (int x = 0; x < N; x ++)
			selflink |= (link[x] >> x & 1) << x;
		for (int x = 0; x < N; x ++)
			link[x] &= ~selflink;

		ull vis = selflink;
		ull ans = 1;
		for (int x = 0; x < N; x ++)
			if (!(vis >> x & 1)) {
				ull S = 1llu << x;
				for (int i = 0; i < N; i ++)
					for (int y = 0; y < N; y ++)
						if (S >> y & 1)
							S |= link[y];
				vis |= S;
				ans *= solve(S, link);
			}

		if (!ans) puts("18446744073709551616");
		else printf("%llu\n", ans);
	}
}
