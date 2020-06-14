#if 0
2020.04.20

* 划分段，极致差分算贡献

枚举 x = j - i ，然后每 x 个位置设一个关键点，那么 [i, j) 一定恰好包含一个关键点。
在两个相邻关键点之间求 lcp, lcs ，然后利用无数次差分算贡献。
求 lcp, lcs 需要用 rank 和 height 优化到 O(1) 。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 500008, mod = 1000000007;
int hb[maxn];
int tmp[maxn], sa2[maxn], t[maxn];

struct SA {
	char s[maxn];
	int sa[maxn], rank[maxn], hi[maxn];
	int st[20][maxn];

	void build(int n, int max) {
		for(int i = 1; i <= n; i ++) {
			rank[i] = s[i];
			sa2[i] = i;
		}

		std::fill(t + 1, t + max + 1, 0);
		for(int i = 1; i <= n; i ++) ++ t[rank[i]];
		for(int i = 1; i <= max; i ++) t[i] += t[i - 1];
		for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
		std::fill(t + 1, t + max + 1, 0);
		int tot = rank[sa[1]] = 1;
		for(int i = 2; i <= n; i ++)
			rank[sa[i]] = s[sa[i]] == s[sa[i - 1]] ? tot : ++ tot;

		for(int m = 1; tot < n; m <<= 1) {
			int p = 0;
			for(int i = 1; i <= m; i ++) sa2[++ p] = n - m + i;
			for(int i = 1; i <= n; i ++) if(sa[i] > m) sa2[++ p] = sa[i] - m;
			for(int i = 1; i <= n; i ++) ++ t[rank[i]];
			for(int i = 1; i <= tot; i ++) t[i] += t[i - 1];
			for(int i = n; i; i --) sa[t[rank[sa2[i]]] --] = sa2[i];
			std::fill(t + 1, t + tot + 1, 0);
			std::copy(rank, rank + n + 1, tmp);
			rank[sa[1]] = tot = 1;
			for(int i = 2; i <= n; i ++)
				rank[sa[i]] = (tmp[sa[i]] == tmp[sa[i - 1]] and
						tmp[sa[i] + m] == tmp[sa[i - 1] + m]) ? tot : ++ tot;
		}

		for(int i = 1; i <= n; i ++) {
			int &k = hi[rank[i]] = std::max(0, hi[rank[i - 1]] - 1);
			while(s[i + k] == s[sa[rank[i] - 1] + k]) ++ k;
		}

		for (int i = n; i; i --) {
			st[0][i] = hi[i];
			for (int k = 1; i + (1 << k) - 1 <= n; k ++)
				st[k][i] = std::min(st[k - 1][i], st[k - 1][i + (1 << k >> 1)]);
		}
	}

	int lcp (int x, int y) {
		x = rank[x], y = rank[y];
		if (x > y) std::swap(x, y);
		++ x;
		int k = hb[y - x + 1];
		return std::min(st[k][x], st[k][y - (1 << k) + 1]);
	}
} A, B;

ll a[maxn], b[maxn], c[maxn], e[maxn];

int main () {
	scanf("%s", A.s + 1);
	int n = int(strlen(A.s + 1));
	for (int i = 1; i <= n; i ++)
		B.s[i] = A.s[n - i + 1];

	for (int i = 2; i <= n; i ++)
		hb[i] = hb[i >> 1] + 1;
	A.build(n, 256);
	B.build(n, 256);

	for (int d = 1; d <= n; d ++) {
		for (int x = d, y = d + d; y <= n; x = y, y += d)
			if (A.s[x] == A.s[y]) {
				int l = std::max(x - B.lcp(n - x + 1, n - y + 1) + 1, x - d + 1);
				int r = x + A.lcp(x, y) - 1;
				int R = std::min(x, r - d);
				if (l <= R) {
					(a[l + d + d] += 1) %= mod;
					(a[R + d + d + 1] -= 1) %= mod;
					(a[r + d + 1] -= R - l + 1) %= mod;
					(a[r + d + 2] += R - l + 1) %= mod;
					(b[l + d + d] += 1 + d) %= mod;
					(b[R + d + d + 1] -= 1 + d) %= mod;
					(b[r + d + 1] -= 1ll * (1 - d) * (R - l + 1)) %= mod;
					(b[r + d + 2] += 1ll * (1 - d) * (R - l + 1)) %= mod;
					(c[l + d + d] -= 1) %= mod;
					(c[R + d + d + 1] += 1) %= mod;
					(e[r + d + 1] += 1ll * (l + R) * (R - l + 1) / 2) %= mod;
				}
			}
	}

	for (int i = 1; i <= n; i ++) (a[i] += a[i - 1]) %= mod;
	for (int i = 1; i <= n; i ++) (a[i] += a[i - 1]) %= mod;
	for (int i = 1; i <= n; i ++) (a[i] = a[i - 1] + a[i] * i) %= mod;

	for (int i = 1; i <= n; i ++) (b[i] += b[i - 1]) %= mod;
	for (int i = 1; i <= n; i ++) (b[i] += b[i - 1]) %= mod;
	for (int i = 1; i <= n; i ++) (b[i] += b[i - 1]) %= mod;

	for (int i = 1; i <= n; i ++) (c[i] += c[i - 1]) %= mod;
	for (int i = 1; i <= n; i ++) (c[i] = c[i - 1] + c[i] * i) %= mod;
	for (int i = 1; i <= n; i ++) (c[i] += c[i - 1]) %= mod;

	for (int i = 1; i <= n; i ++) (e[i] += e[i - 1]) %= mod;
	for (int i = 1; i <= n; i ++) (e[i] += e[i - 1]) %= mod;

	for (int i = 1; i <= n; i ++)
		printf("%lld\n", (a[i] + b[i] + c[i] + e[i] + ll(mod) * 4) % mod);
}
