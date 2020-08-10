/*
 * Author: Kewth

 * Date:
  2020.08.04

 * Solution:
 * 二进制分组，整体二分，随机化

  把所有部分分都写了一遍，妙啊。

  关键思路有两个：二进制分组和整体二分。

  通过二进制分组以 nlog 的操作次数简单得到每个点连接点的编号异或和。这就可以直接做匹配了，
推广一下可以做链，再加个重编号（每个点有两个不同编号，对两种编号分别二进制分组）就可以通
过树的部分。

  整体二分的思路在于对于一个点 u 和点集 S ，如果点亮 S 的所有点后 u 也亮了，说明 u 和 S
之间有奇数条边。如果 |S| = 1 就可以确定一条边了，否则任意选一个 S 的划分 A, B ，由于奇数
分解成两个数的和一定是一个奇数一个偶数，可以把 S 替换为 A 或 B 继续处理直到 |S| = 1 。
直接这样做就能过有根树的部分，但这个做法很好推广，每次随机选择一个点集 S 做整体二分，完
全可以套用到一般图的情况。

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
#include <algorithm>
#include <vector>
#include <set>
#include <random>

void modify(int);
int query(int);
void report(int, int);
int check(int);
void explore(int, int);

/* #include "explore.h" */

#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

const int maxn = 200000;
std::mt19937 e;

namespace FORCE {
	const int maxn = 500;
	bool las[maxn];
	bool link[maxn][maxn];
	void main (int n, int) {
		for (int i = 0; i < n - 1; i ++) {
			modify(i);
			for (int j = 0; j <= i; j ++)
				if (link[j][i] or j == i)
					las[j] ^= 1;
			for (int j = i + 1; j < n; j ++) {
				bool now = query(j);
				if (now != las[j])
					link[i][j] = 1, report(i, j);
				las[j] = now;
			}
		}
	}
};

namespace MATCH {
	int match[maxn];
	void main (int n, int) {
		for (int k = 0; (1 << k) < n; k ++) {
			for (int i = 0; i < n; i ++) if (i >> k & 1) modify(i);
			for (int i = 0; i < n; i ++)
				if (query(i) != (i >> k & 1))
					match[i] |= 1 << k;
			for (int i = 0; i < n; i ++) if (i >> k & 1) modify(i);
		}
		for (int i = 0; i < n; i ++)
			if (i < match[i])
				report(i, match[i]);
	}
};

namespace RTREE {
	int fa[maxn];
	void solve (std::vector<int> s, int l, int r) {
		if (l == r) {
			for (int u : s) fa[u] = l;
			return;
		}
		int m = (l + r) >> 1;
		for (int i = l; i <= m; i ++) modify(i);
		std::vector<int> s1, s2;
		for (int u : s) (u <= m or query(u) ? s1 : s2).push_back(u);
		for (int i = l; i <= m; i ++) modify(i);
		solve(s1, l, m);
		solve(s2, m + 1, r);
	}
	void main (int n, int) {
		std::vector<int> s;
		for (int i = 0; i < n; i ++) s.push_back(i);
		solve(s, 0, n - 1);
		for (int i = 1; i < n; i ++) report(fa[i], i);
	}
};

namespace CHAIN {
	int match[maxn], stack[maxn], sp;
	void main (int n, int) {
		for (int k = 0; (1 << k) < n; k ++) {
			for (int i = 0; i < n; i ++) if (i >> k & 1) modify(i);
			for (int i = 0; i < n; i ++)
				if (query(i) != (i >> k & 1))
					match[i] |= 1 << k;
			for (int i = 0; i < n; i ++) if (i >> k & 1) modify(i);
		}
		modify(0);
		for (int i = 1; i < n; i ++)
			if (query(i))
				report(0, i), stack[++ sp] = i;
		while (sp) {
			int u = stack[sp --], v = match[u];
			if (!v) continue;
			report(u, v);
			stack[++ sp] = v;
			match[v] ^= u;
		}
	}
};

namespace TREE {
	int match[maxn], pmatch[maxn], p[maxn], stack[maxn], sp;
	bool isleaf (int u, int n) {
		if (match[u] == 0 or match[u] > n or pmatch[u] > n) return 0;
		if (p[match[u] - 1] != pmatch[u]) return 0;
		return 1;
	}
	void main (int n, int) {
		for (int i = 0; i < n; i ++) p[i] = i + 1;
		for (int k = 0; (1 << k) <= n; k ++) {
			for (int i = 0; i < n; i ++) if (p[i] >> k & 1) modify(i);
			for (int i = 0; i < n; i ++)
				if (query(i) != (p[i] >> k & 1))
					match[i] |= 1 << k;
			for (int i = 0; i < n; i ++) if (p[i] >> k & 1) modify(i);
		}
		std::shuffle(p, p + n, e);
		for (int k = 0; (1 << k) <= n; k ++) {
			for (int i = 0; i < n; i ++) if (p[i] >> k & 1) modify(i);
			for (int i = 0; i < n; i ++)
				if (query(i) != (p[i] >> k & 1))
					pmatch[i] |= 1 << k;
			for (int i = 0; i < n; i ++) if (p[i] >> k & 1) modify(i);
		}
		/* for (int i = 0; i < n; i ++) */
		/* 	debug("%d %d %d | %d\n", p[i], match[i], pmatch[i], isleaf(i, n)); */
		for (int i = 0; i < n; i ++) if (isleaf(i, n)) stack[++ sp] = i;
		while (sp) {
			int u = stack[sp --], v = match[u] - 1;
			if (v == -1) continue;
			report(u, v);
			match[v] ^= u + 1;
			pmatch[v] ^= p[u];
			if (isleaf(v, n)) stack[++ sp] = v;
		}
	}
};

namespace FULL {
	bool mark[maxn], ok[maxn];
	int p[maxn], tot;
	std::set<int> G[maxn];
	std::vector<int> L[maxn];
	int shit[maxn], s1[maxn], s2[maxn];
	inline void modify (int u) {
		if (ok[u]) return;
		::modify(u);
		for (int v : G[u]) mark[v] ^= 1;
	}
	inline bool query (int u) {
		return ::query(u) ^ mark[u];
	}
	inline void report (int u, int v) {
		if (G[u].count(v) or G[v].count(u)) return;
		::report(u, v);
		++ tot;
		G[u].insert(v);
		G[v].insert(u);
		ok[u] = ::check(u);
		ok[v] = ::check(v);
	}
	void solve (int s, int t, int l, int r) {
		if (s > t) return;
		/* for (int u : s) debug(" %d", u); debug(" |"); */
		/* for (int i = l; i <= r; i ++) debug(" %d", p[i]); debug("\n"); */
		if (l == r) {
			for (int i = s; i <= t; i ++)
				L[shit[i]].push_back(p[l]);
			return;
		}
		int m = (l + r) >> 1;
		for (int i = l; i <= m; i ++) modify(p[i]);
		int p1 = 0, p2 = 0;
		for (int i = s; i <= t; i ++)
			(query(shit[i]) ? s1[++ p1] : s2[++ p2]) = shit[i];
		for (int i = l; i <= m; i ++) modify(p[i]);
		std::copy(s1 + 1, s1 + p1 + 1, shit + s);
		std::copy(s2 + 1, s2 + p2 + 1, shit + s + p1);
		solve(s, s + p1 - 1, l, m);
		solve(s + p1, s + p1 + p2 - 1, m + 1, r);
	}
	void main (int n, int M) {
		for (int i = 0; i < n; i ++) G[i].insert(i), p[i] = i;
		while (tot < M) {
			std::shuffle(p, p + n, e);
			int m = n >> 1;
			for (int i = 0; i < m; i ++) modify(p[i]);
			int sp = 0;
			for (int i = 0; i < n; i ++)
				if (!ok[i] and query(i))
					shit[++ sp] = i;
			for (int i = 0; i < m; i ++) modify(p[i]);
			/* debug("search\n"); */
			solve(1, sp, 0, m - 1);
			for (int i = 1; i <= sp; i ++) {
				for (int v : L[shit[i]])
					report(shit[i], v);
				L[shit[i]].clear();
			}
		}
	}
};

void explore (int n, int m) {
	/* FULL::main(n, m); */
	if (n % 10 == 8) MATCH::main(n, m);
	else if (n % 10 == 7) RTREE::main(n, m);
	else if (n % 10 == 6) CHAIN::main(n, m);
	else if (n % 10 == 5) TREE::main(n, m);
	else if (n <= 500) FORCE::main(n, m);
	else FULL::main(n, m);
}
