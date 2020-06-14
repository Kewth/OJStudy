/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
    2020.06.11

 * Solution:
 * 问题转换，分离算贡献，线段树

    考虑联通块数量的本质是什么，首先得考虑一个联通块的性质。观察一号点所在的联通块，不难
发现其必然是一段前缀，满足该前缀的最小值大于其他点的最大值。然后可以把这个联通块删掉，转
为规模更小的同样的问题，不难归纳出联通块的数量就是一种分界的数量，要满足分界左边的数都大
于分界右边的数。

    然而分界的数量仍然难以直接维护，对于一个分界，设其左边的最小值为 x ，不妨把这个分界
的贡献算在 x 上，首先一个权值最多只有一个贡献，那么对于一个存在的权值 x ，把 >= x 的数设
为 1 ，反之为 0 ，可以发现该值有贡献当且仅当所有 1 全部在所有 0 左边。

    考虑高效维护有贡献的 x 的数量，设 f(x) 表示有多少相邻的数满足左 1 右 0 ，观察 f(x) 的
性质，不难发现 f(x) >= 1 ，x 有贡献当且仅当 f(x) = 1 ，特别地，由于有贡献的 x 必须出现，
不妨令没有出现的 x 有 f(x) = INF 。这样一来，只需要用线段树维护 f ，答案就是最小值的数量。
容易发现每次修改一个点影响到的 f 的数量是 O(1) 的。

 * Digression:
    完全没有想到对于每个权值单独算贡献，一直在想维护连续段，技不如人啊。

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

const int maxn = 500005;
int a[maxn], b[maxn << 2];
int min[maxn << 3], tot[maxn << 3], tag[maxn << 3];
#define ls (now << 1)
#define rs (now << 1 | 1)

inline void modi (int now, int x) { min[now] += x; tag[now] += x; }

void push (int now) {
	if (tag[now]) {
		modi(ls, tag[now]);
		modi(rs, tag[now]);
		tag[now] = 0;
	}
}

void update (int now) {
	min[now] = std::min(min[ls], min[rs]);
	tot[now] = 0;
	if (min[ls] == min[now]) tot[now] += tot[ls];
	if (min[rs] == min[now]) tot[now] += tot[rs];
}

void modify (int now, int L, int R, int l, int r, int x) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return modi(now, x);
	push(now);
	int M = (L + R) >> 1;
	modify(ls, L, M, l, r, x);
	modify(rs, M + 1, R, l, r, x);
	update(now);
}

void build (int now, int L, int R) {
	if (L == R) {
		min[now] = !b[L];
		tot[now] = 1;
		return;
	}
	int M = (L + R) >> 1;
	build(ls, L, M);
	build(rs, M + 1, R);
	update(now);
}

int main () {
	int n = read, q = read;
	int L = 1, R = 1000001;
	a[0] = R - 1;
	a[n + 1] = L - 1;
	for (int i = 1; i <= n; i ++)
		++ b[a[i] = read];
	build(1, L, R);

	modify(1, L, R, a[1] + 1, R, 1);
	for (int i = 1; i <= n; i ++)
		if (a[i] > a[i + 1])
			modify(1, L, R, a[i + 1] + 1, a[i], 1);

	while (q --) {
		int p = read, x = read;
		if (a[p - 1] > a[p])
			modify(1, L, R, a[p] + 1, a[p - 1], -1);
		if (a[p] > a[p + 1])
			modify(1, L, R, a[p + 1] + 1, a[p], -1);
		if (-- b[a[p]] == 0)
			modify(1, L, R, a[p], a[p], 1);
		a[p] = x;
		if (++ b[a[p]] == 1)
			modify(1, L, R, a[p], a[p], -1);
		if (a[p - 1] > a[p])
			modify(1, L, R, a[p] + 1, a[p - 1], 1);
		if (a[p] > a[p + 1])
			modify(1, L, R, a[p + 1] + 1, a[p], 1);
		printf("%d\n", tot[1]);
	}
}
