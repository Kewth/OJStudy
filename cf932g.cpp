/*
 * Author: Kewth

 * Date:
  2020.07.22

 * Solution:
 * 问题转换，设计 DP ，PAM ，border

  构造串 T = S[1] S[n] S[2] S[n - 2] ... ，可以发现在 T 上问题可以转换为将 T 划分为若
干偶数长的回文串的方案数。

  设计 DP f[i] 表示前缀 i 的答案，朴素转移枚举回文后缀，这个转移放在 PAM 上就是一直跳
fail 。依据 border 那套理论，考虑把一段等差数列放一起处理。

  设 g[u] 表示 u 节点一直跳 fail 跳出等差数列前所有对应 f 的和，但每次一条链上的所有 g
都会发生变化，没法全部维护。

  blablabla 所以只要修改跳等差数列时经过的 g 就行了。不懂了，网上所有题解都没有提到这
个原因（甚至包括官方题解在内许多都没有提到 g ），在别人眼里这是很自然的一步？

  -----UPDATE: 好像悟了。-----

  设位置 i 跳 slink 跳到的节点集合为 S(i) ，现在要证明的是，对于 S(i) 中的任意一个满足
u != top[u] 的节点 u ，S(i - dt[u]) 中包含了 fail[u] 。

  不难发现位置 i - dt[u] 跳 fail 一定能调到 fail[u] ，那么要证明的也就是 fail[u] 是划
分的等差数列的开头，也就是说 fail[u] 没有子节点或者 fail[u] 的子节点 v 满足 top[v] = v ，
即 dt[v] != dt[fail[u]] 。这里子节点是对于位置 i - dt[u] 到根形成的链而言的。

  反证法，如果 dt[fail[u]] = dt[v] ，可以发现 v = u ，那么在位置 i 形成的链上 u 的子节
点 x 一定满足 dt[x] = dt[u] ，换言之 u 不属于 S(i) ，矛盾。

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 1000005, maxc = 26, mod = 1000000007;
char s[maxn], t[maxn];
int ch[maxn][maxc], fail[maxn], len[maxn], dt[maxn], top[maxn], cp = 2;
int pos[maxn];
ll f[maxn], g[maxn];

int main () {
	scanf("%s", s + 1);
	int n = int(strlen(s + 1));
	for (int i = 1; i <= n / 2; i ++) {
		t[i * 2 - 1] = s[i];
		t[n - i * 2 + 2] = s[n / 2 + i];
	}

	len[1] = -1;
	len[2] = 0;
	fail[2] = 1;
	/* dt[2] = 1; */
	dt[2] = -1; // 避免 2 号节点和其他节点并在同一条链上
	top[2] = 2;

	pos[0] = 1;
	for (int i = 1; i <= n; i ++) {
		int pre = pos[i - 1], c = t[i] - 'a';
		while (t[i - len[pre] - 1] != t[i]) pre = fail[pre];
		int &now = ch[pre][c];
		if (!now) {
			now = ++ cp;
			len[now] = len[pre] + 2;
			if (pre == 1) fail[now] = 2;
			else {
				pre = fail[pre];
				while (t[i - len[pre] - 1] != t[i]) pre = fail[pre];
				fail[now] = ch[pre][c];
			}
			dt[now] = len[now] - len[fail[now]];
			top[now] = dt[now] == dt[fail[now]] ? top[fail[now]] : now;
		}
		pos[i] = now;
	}

	f[0] = 1;
	for (int i = 1; i <= n; i ++) {
		ll sum = 0;
		for (int x = pos[i], y; x > 2; x = fail[y]) {
			y = top[x];
			g[x] = f[i - len[y]];
			// 这里的 g[fail[x]] 一定是在 i - dt[x] 被更新过的正确值
			if (y != x) g[x] += g[fail[x]];
			sum += g[x];
		}
		if (!(i & 1)) f[i] = sum % mod;
		/* for (int j = 3; j <= cp; j ++) debug(" %lld", g[j]); debug("\n"); */
	}

	printf("%lld\n", f[n]);
	/* debug("%s\n", t + 1); */
}
