/*
 * Author: Kewth

 * Date:
  2020.07.20

 * Solution:
 * 二分，双关键字分块

  放在 dfs 序上问题不难转换为区间加和区间第 k 小。这个问题似乎没有什么特别优秀的做法。

  考虑二分答案，问题转换为询问区间有多少数不超过 M ，不难想到值域分块，但是带上区间就
比较鬼畜。来一手双关键字分块，将序列分为若干块，保证每一块的极差不超过 B1 ，大小不超过
B2 ，注意到值域最大是 n * l = 1e6 ，这样分块块的大小不会太大，是 O(nl/B1+n/B2) 的。

  但是由于序列的值会随着操作发生该变，分块的结构不可能是一成不变的，因此要用链表的结构
存储分块，能够随时调整分块结构，事实上就是一个块状链表。当然，定期重构也是可以的。

  于是区间加就可以打标记，这个操作可能把一个完整的块拆成两个块。区间查询同样要拆开，然
后每个块内用桶记录权值，二分的时候直接扫每个块查询即可。拆块会使块的数量增加，所以每当
有两个相邻块可以合并的时候要合并以保证块的数量。

  带上二分，这个复杂度大概是 O(n sqrt(nlog)) 的形式，跑起来很吃力。

 * Digression:
  卡空间，nsqrt 的空间开不下，由于块的数量始终不会到 O(n) ，动态分配即可。
  需要大量调用 std::min, std::max 的时候，手写效率明显更高。

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

#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxs = 4000, B1 = 3600, B2 = 500;
short Tot[maxs][B1];
struct Block {
	int min, max, tag, tid;
};

bool mark[maxs + 1];
Block b[maxn];
int nxt[maxn];
std::vector<int> G[maxn];
int fa[maxn], faw[maxn];
int id[maxn], iid[maxn], size[maxn], ip;
int dis[maxn];

inline int min (int x, int y) { return x < y ? x : y; }
inline int max (int x, int y) { return x > y ? x : y; }

int newid () {
	static int tp;
	++ tp;
	while (mark[tp]) ++ tp;
	if (tp == maxs) {
		memset(mark, 0, sizeof mark);
		for (int i = 1; b[i].tid; i = nxt[i])
			mark[b[i].tid] = 1;
		tp = 1;
		while (mark[tp]) ++ tp;
	}
	return tp;
}

void dfs (int u) {
	iid[id[u] = ++ ip] = u;
	size[u] = 1;
	for (int v : G[u]) {
		dfs(v);
		size[u] += size[v];
	}
}

void push (int p) {
	if (!b[p].tag) return;
	for (int i = p; i < nxt[p]; i ++)
		dis[i] += b[p].tag;
	b[p].max += b[p].tag;
	b[p].min += b[p].tag;
	b[p].tag = 0;
}

void make (int l, int r) {
	if (!l and !r) return;
	b[l].min = 1000000000, b[l].max = 0;
	for (int i = l; i <= r; i ++) {
		b[l].min = min(b[l].min, dis[i]);
		b[l].max = max(b[l].max, dis[i]);
	}
	if (!b[l].tid) b[l].tid = newid();
	short *tot = Tot[b[l].tid];
	memset(tot, 0, sizeof Tot[b[l].tid]);
	for (int i = l; i <= r; i ++)
		++ tot[dis[i] - b[l].min];
	for (int x = 1; x <= b[l].max - b[l].min; x ++)
		tot[x] += tot[x - 1];
}

void build (int n) {
	int pre = 0;
	for (int i = 1; i <= n; i ++) {
		if (!pre or i >= pre + B2 or
				dis[i] >= b[pre].min + B1 or dis[i] <= b[pre].max - B1) {
			nxt[pre] = i;
			make(pre, i - 1);
			pre = i;
			b[i].min = b[i].max = dis[i];
		}
		b[pre].min = min(b[pre].min, dis[i]);
		b[pre].max = max(b[pre].max, dis[i]);
	}
	nxt[pre] = n + 1;
	make(pre, n);
}

void split (int l) {
	int p = 1;
	while (nxt[p] <= l) p = nxt[p];
	if (p == l) return;
	make(p, l - 1);
	make(l, nxt[p] - 1);
	b[l].tag = b[p].tag;
	nxt[l] = nxt[p];
	nxt[p] = l;
}

int main () {
	int n = read, q = read;
	read.operator int();
	for (int u = 2; u <= n; u ++) {
		G[fa[u] = read].push_back(u);
		faw[u] = read;
	}

	dfs(1);

	for (int i = 1; i <= n; i ++) {
		int u = iid[i];
		dis[i] = dis[id[fa[u]]] + faw[u];
	}

	build(n);

	while (q --) {
		int o = read;

		if (o == 1) {
			int u = read, k = read;
			if (k > size[u]) {
				puts("-1");
				continue;
			}

			int l = id[u], r = id[u] + size[u] - 1;
			split(l);
			if (r < n) split(r + 1);

			int L = 1000000000, R = 0;
			for (int p = l; p <= r; p = nxt[p])
				L = min(L, b[p].min + b[p].tag), R = max(R, b[p].max + b[p].tag);
			while (L < R) {
				int M = (L + R) >> 1;
				int tot = 0;
				for (int p = l; p <= r; p = nxt[p])
					if (b[p].min + b[p].tag <= M)
						tot += Tot[b[p].tid][min(M - b[p].min - b[p].tag,
								b[p].max - b[p].min)];
				if (k <= tot) R = M;
				else L = M + 1;
			}
			printf("%d\n", L);
		}

		if (o == 2) {
			int u = read, x = read;
			int l = id[u], r = id[u] + size[u] - 1;
			split(l);
			if (r < n) split(r + 1);
			for (int p = l; p <= r; p = nxt[p])
				b[p].tag += x;
		}

		for (int p = 1; p <= n and nxt[p] <= n; p = nxt[p]) {
			int np = nxt[p];
			if (max(b[p].max + b[p].tag, b[np].max + b[np].tag) -
					min(b[p].min + b[p].tag, b[np].min + b[np].tag) < B1 and
					nxt[np] - 1 - p < B2) {
				push(p);
				push(np);
				make(p, nxt[np] - 1);
				nxt[p] = nxt[np];
				b[np].tid = 0;
			}
		}
	}
}
