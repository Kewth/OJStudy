#if 0
2020.02.19

以下左、右、之间，都是指所在列的关系。
分三类：起点在终点左边，起点在终点右边，起点与终点在同一列。

考虑起点在终点左边的情况，将路径分为三段：
不在起点右边，不在终点左边，在起点终点之间。

对于第一段，要么是一个单独的点，要么是个向左凸的 U 形路径。
设 len[i][j][k] 表示 (i, j) 为该段最后的点，该段长度为 k 的方案数。
事实上方案数非 0 即 1 ，因为只要 i, j, k 确定该段的形状就确定了，
只需要用 Hash 判断一下该形状是否能匹配上即可。

第二段与第一段类似，考虑第三段。
设 f[i][j][k] 表示 (i, j) 为该段最后的点，上一个点为 (i, j -1) ，
该段长度为 k 的方案数。
设 g[i][j][k] 表示 (i, j) 为该段最后的点，上一个点为 (i +/- 1, j) ，
该段长度为 k 的方案数。
转移很简单，略。

而起点在终点右边的情况和起点在终点左边类似。
起点和终点在同一列的情况用上述的 len 即可计算。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long hash;

const int maxn = 2005, mod = 1000000007;
const hash base = 131;
char s[3][maxn], t[maxn];
int f[3][maxn][maxn], g[3][maxn][maxn];
bool llen[3][maxn][maxn], rlen[3][maxn][maxn];
hash pre[3][maxn], suf[3][maxn];
hash tpre[maxn], tsuf[maxn];
hash po[maxn];

ll solve(int n, int m) {
	for(int i = 1; i <= 2; i ++) {
		for(int j = 1; j <= n; j ++)
			pre[i][j] = pre[i][j - 1] * base + hash(s[i][j] - 'a' + 1);
		for(int j = n; j; j --)
			suf[i][j] = suf[i][j + 1] * base + hash(s[i][j] - 'a' + 1);
	}

	for(int i = 1; i <= 2; i ++) {
		int ri = 3 - i;
		for(int j = 1; j <= n; j ++) {
			llen[i][j][1] = s[i][j] == t[1];
			for(int k = 2; k <= m and k / 2 <= j; k += 2)
				llen[i][j][k] = tpre[k] ==
					pre[i][j] - pre[i][j - k / 2] * po[k / 2] +
					suf[ri][j - k / 2 + 1] * po[k / 2] -
					suf[ri][j + 1] * po[k];

			rlen[i][j][1] = s[i][j] == t[m];
			for(int k = 2; k <= m and j + k / 2 - 1 <= n; k += 2)
				rlen[i][j][k] = tsuf[m - k + 1] ==
					suf[i][j] - suf[i][j + k / 2] * po[k / 2] +
					pre[ri][j + k / 2 - 1] * po[k / 2] -
					pre[ri][j - 1] * po[k];
		}
	}

	for(int k = 1; k <= m; k ++)
		for(int i = 1; i <= 2; i ++)
			for(int j = 1; j <= n; j ++)
				if(s[i][j] == t[k]) {
					f[i][j][k] = (0ll + llen[i][j - 1][k - 1] +
							f[i][j - 1][k - 1] + g[i][j - 1][k - 1]) % mod;
					g[i][j][k] = f[3 - i][j][k - 1];
				}

	ll res = 0;
	for(int i = 1; i <= 2; i ++)
		for(int j = 1; j <= n; j ++)
			for(int k = 1; k <= m; k ++)
				if(rlen[i][j][k])
					res += f[i][j][m - k + 1];
	res %= mod;
	return res;
}

int main() {
	po[0] = 1;
	for(int i = 1; i < maxn; i ++)
		po[i] = po[i - 1] * base;

	scanf("%s%s%s", s[1] + 1, s[2] + 1, t + 1);
	int n = int(strlen(s[1] + 1)), m = int(strlen(t + 1));

	for(int i = 1; i <= m; i ++)
		tpre[i] = tpre[i - 1] * base + hash(t[i] - 'a' + 1);
	for(int i = m; i; i --)
		tsuf[i] = tsuf[i + 1] * base + hash(t[i] - 'a' + 1);

	ll ans = solve(n, m);
	// debug("%lld\n", ans);

	for(int i = 1; i <= 2; i ++)
		for(int j = 1; j <= n; j ++)
			ans += llen[i][j][m];

	if(m > 2)
		for(int i = 1; i <= 2; i ++)
			for(int j = 1; j <= n; j ++)
				ans += rlen[i][j][m];
	// debug("%lld\n", ans);

	memset(llen, 0, sizeof llen);
	memset(rlen, 0, sizeof rlen);
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);

	std::reverse(s[1] + 1, s[1] + n + 1);
	std::reverse(s[2] + 1, s[2] + n + 1);
	ans += solve(n, m);
	ans %= mod;

	printf("%lld\n", ans);
}
