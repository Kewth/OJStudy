/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.07

 * Solution:
  如果询问只有 [1, n] ，问题就很经典，用扫描线 + 线段树维护每个点作为当前扫描线的左端
点的 max - min - r + l 即可。
  如果询问 [l, r] 只需要考虑右端点在 r ，左端点在 [l, r] 内的子区间也很好求，离线下来
挂在扫描线上，线段树来个区间求和即可。
  而右端点也不是固定的了，那么实际上 [l, r] 内的点在每个时刻变为 0 都对该询问有 1 的
贡献，也就是要在线段树上维护节点历史版本贡献和。不妨加一个时间推移操作表示把每个点当
前的状态贡献入答案，那么这个操作也可以打标记维护，但是和区间加混在一起就很迷，标记的
先后顺序以及下传都不是很自然的一个过程，具体过程很复杂，不写了。

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
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 120005;
ll his[maxn << 2];
int min[maxn << 2], tot[maxn << 2], mot[maxn << 2], pat[maxn << 2];
#define ls (now << 1)
#define rs (now << 1 | 1)

void modi (int now, int x) {
	min[now] += x;
	mot[now] += x;
}

void pass (int now, int x) {
	his[now] += 1ll * tot[now] * x;
	pat[now] += x;
}

void push (int now) {
	if (mot[now]) {
		modi(ls, mot[now]);
		modi(rs, mot[now]);
		mot[now] = 0;
	}
	if (pat[now]) {
		if (min[ls] == min[now]) pass(ls, pat[now]);
		if (min[rs] == min[now]) pass(rs, pat[now]);
		pat[now] = 0;
	}
}

void modify (int now, int L, int R, int l, int r, int x) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return modi(now, x);
	push(now);
	int M = (L + R) >> 1;
	modify(ls, L, M, l, r, x);
	modify(rs, M + 1, R, l, r, x);
	his[now] = his[ls] + his[rs];
	min[now] = std::min(min[ls], min[rs]);
	tot[now] = 0;
	if (min[ls] == min[now]) tot[now] += tot[ls];
	if (min[rs] == min[now]) tot[now] += tot[rs];
}

ll query (int now, int L, int R, int l, int r) {
	if (r < L or l > R) return 0;
	if (l <= L and R <= r) return his[now];
	push(now);
	int M = (L + R) >> 1;
	return query(ls, L, M, l, r) + query(rs, M + 1, R, l, r);
}

void build (int now, int L, int R) {
	min[now] = L;
	tot[now] = 1;
	if (L == R) return;
	int M = (L + R) >> 1;
	build(ls, L, M);
	build(rs, M + 1, R);
}

void test (int now, int L, int R) {
	if (L == R) {
		debug(" %d", min[now]);
		return;
	}
	push(now);
	int M = (L + R) >> 1;
	test(ls, L, M);
	test(rs, M + 1, R);
	if (now == 1) debug("\n");
}

int a[maxn];
ll ans[maxn];
int st1[maxn], sp1;
int st2[maxn], sp2;
std::vector<par> v[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	int q = read;
	for (int i = 1; i <= q; i ++) {
		int l = read, r = read;
		v[r].push_back(par(l, i));
	}

	build(1, 1, n);
	for (int r = 1; r <= n; r ++) {
		while (sp2 and a[st2[sp2]] > a[r])
			modify(1, 1, n, st2[sp2 - 1] + 1, st2[sp2], a[st2[sp2]]), -- sp2;
		st2[++ sp2] = r;
		modify(1, 1, n, st2[sp2 - 1] + 1, st2[sp2], - a[st2[sp2]]);

		while (sp1 and a[st1[sp1]] < a[r])
			modify(1, 1, n, st1[sp1 - 1] + 1, st1[sp1], - a[st1[sp1]]), -- sp1;
		st1[++ sp1] = r;
		modify(1, 1, n, st1[sp1 - 1] + 1, st1[sp1], a[st1[sp1]]);

		modi(1, -1);
		pass(1, 1);
		/* test(1, 1, n); */

		for (par p : v[r])
			ans[p.second] = query(1, 1, n, p.first, r);
	}

	for (int i = 1; i <= q; i ++)
		printf("%lld\n", ans[i]);
}
