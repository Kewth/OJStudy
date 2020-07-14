/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.07.05

 * Solution:
  将两个串拼接起来，那么问题可以转换为对于若干个后缀，有 A, B 两类，要求两两匹配使得
贡献最大，其中两个后缀匹配的贡献为 min(lcp, K) 。
  涉及到后缀的 lcp ，不难想到后缀排序和 height 数组，那么问题可以进一步转换，有一个
01 序列，要将 0 和 1 两两匹配最大化贡献，两个点的贡献是它们之间构成的区间的 height 的
最小值。对于 height 数组建小根笛卡尔树，在笛卡尔树上不难得到一个正确的递归贪心，略去。

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
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 300005;
char s[maxn];
int sa[maxn], rank[maxn], hi[maxn];
int tmp[maxn], sa2[maxn];

void build (int n, int max) {
	for (int i = 1; i <= n; i ++) rank[i] = s[i], sa2[i] = i;

	std::fill(tmp + 1, tmp + n + 1, 0);
	for (int i = 1; i <= n; i ++) ++ tmp[rank[i]];
	for (int i = 1; i <= max; i ++) tmp[i] += tmp[i - 1];
	for (int i = n; i; i --) sa[tmp[rank[sa2[i]]] --] = sa2[i];
	max = 1;
	rank[sa[1]] = 1;
	for (int i = 2; i <= n; i ++)
		rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? max : ++ max;

	for (int m = 1; max < n; m <<= 1) {
		int p = 0;
		for (int i = 0; i < m; i ++) sa2[++ p] = n - i;
		for (int i = 1; i <= n; i ++) if (sa[i] > m) sa2[++ p] = sa[i] - m;
		std::fill(tmp + 1, tmp + n + 1, 0);
		for (int i = 1; i <= n; i ++) ++ tmp[rank[i]];
		for (int i = 1; i <= max; i ++) tmp[i] += tmp[i - 1];
		for (int i = n; i; i --) sa[tmp[rank[sa2[i]]] --] = sa2[i];
		std::copy(rank, rank + n + 1, tmp);
		max = rank[sa[1]] = 1;
		for (int i = 2; i <= n; i ++)
			rank[sa[i]] = tmp[sa[i]] == tmp[sa[i - 1]] and
				tmp[sa[i] + m] == tmp[sa[i - 1] + m] ? max : ++ max;
	}

	for (int i = 1; i <= n; i ++) {
		int &k = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
		while (s[i + k] == s[sa[rank[i] - 1] + k]) ++ k;
	}
}

int stack[maxn], sp;
int ls[maxn], rs[maxn];
int apre[maxn], bpre[maxn];

ll ans;
void solve (int x, int l, int r) {
	if (!x) return;
	int a1 = apre[x - 1] - apre[l - 2];
	int b1 = bpre[x - 1] - bpre[l - 2];
	int a2 = apre[r] - apre[x - 1];
	int b2 = bpre[r] - bpre[x - 1];
	if (a1 >= b1 and b2 >= a2)
		ans -= hi[x] * std::min(a1 - b1, b2 - a2);
	else if (a1 < b1 and b2 < a2)
		ans -= hi[x] * std::min(b1 - a1, a2 - b2);
	solve(ls[x], l, x - 1);
	solve(rs[x], x + 1, r);
}

int main () {
	int n = read, m = read, N = n << 1;
	scanf("%s", s + 1);
	scanf("%s", s + n + 1);
	build(N, 256);

	for (int i = 2; i <= N; i ++) {
		hi[i] = std::min(hi[i], m);
		while (sp and hi[stack[sp]] >= hi[i])
			ls[i] = stack[sp --];
		if (sp) rs[stack[sp]] = i;
		stack[++ sp] = i;
	}

	for (int i = 1; i <= N; i ++)
		if (sa[i] <= n - m + 1)
			apre[i] = 1;
		else if (sa[i] > n and sa[i] <= N - m + 1)
			bpre[i] = 1;

	for (int i = 2; i <= N; i ++)
		apre[i] += apre[i - 1], bpre[i] += bpre[i - 1];

	ans = 1ll * (n - m + 1) * m;
	solve(stack[1], 2, N);
	printf("%lld\n", ans);
}
