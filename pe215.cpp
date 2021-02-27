/*
 * Author: Kewth

 * Date:
  2021.01.26

 * Solution:
  把一行所有可能的状态搜出来作为节点考虑建图，如果两个状态可以相邻就连边。
  w = 45 时该图的点数和边数大概是 1e5, 1e6 的级别。
  但是暴力连边的复杂度是点数平方的，用一个二进制数（缝隙位置集合状压后的值）表示一个节点，
那么两个节点有边当且仅当它们按位与为零。可以把二进制位拆成两部分，对于前半部分的每种可能
的值开一个桶存入后半部分的值，然后连边的时候先扫描所有有值的桶，然后在有用的桶内逐一枚举
所有值判断是否有边即可。

 * Digression:
  又是 jb 搜索题？

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxi = 200000, B = 28;
ll f[maxi], g[maxi];
ll s[maxi];
std::map<ll, int> bmap;
std::vector<int> block[maxi], G[maxi];
int bs[maxi];
int sp, bp;

void dfs (int m, int x, ll S) {
	if (x > m) return;
	if (x == m) {
		S ^= (1ll << m);
		s[++ sp] = S;
		int &b = bmap[S & ((1 << B) - 1)];
		if (!b) bs[b = ++ bp] = S & ((1 << B) - 1);
		block[b].push_back(sp);
		return;
	}
	dfs(m, x + 2, S | (1ll << (x + 2)));
	dfs(m, x + 3, S | (1ll << (x + 3)));
}

int main () {
#ifdef PE
	int m = 40, n = 10, mod = 0;
#else
	int m = read, n = read, mod = read;
#endif
	dfs(m, 0, 0);
	int TOT = 0;
	for (int j = 1; j <= sp; j ++)
		for (int k = 1; k <= bp; k ++)
			if ((s[j] & bs[k]) == 0)
				for (int l : block[k])
					if ((s[j] & s[l]) == 0)
						++ TOT,
						G[j].push_back(l);
	debug("%d %d\n", sp, TOT);
	std::fill(f + 1, f + sp + 1, 1);
	for (int i = 2; i <= n; i ++) {
		std::copy(f, f + sp + 1, g);
		std::fill(f + 1, f + sp + 1, 0);
		for (int j = 1; j <= sp; j ++)
			for (int l : G[j])
				f[j] += g[l];
		if (mod)
			for (int j = 1; j <= sp; j ++)
				f[j] %= mod;
	}
	ll ans = 0;
	for (int i = 1; i <= sp; i ++)
		ans += f[i];
	printf("%lld\n", mod ? ans % mod : ans);
}
