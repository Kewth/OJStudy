/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.16

 * Solution:
 * 问题转换（量化地描述问题），线段树动态维护分治结构

    对于一个权值 w ，设其出现的位置集合为 S[w] ，l = min(S[w]), r = max(S[w]) ，那么
最终序列里 [l, r] 必须是同一个权值，不妨缩为一段。最后序列被分为若干段，那么花费显然
就是 n 减去每一段出现次数最多的值的出现次数。

    乍一看不好维护，首先为了很好的描述这个分段，设一个辅助数组 {a} ，a[i] = 1 当且仅
当原序列 i 和 i + 1 在同一段，那么对于每个权值 w ，其对 {a} 的影响就是一个区间覆盖。
如果要求的是段数，用个线段树维护 {a} 即可，但是区间覆盖难以逆操作，不妨扩展 {a} 的定
义，把是否覆盖改为覆盖次数，那么维护 {a} 的最小值和最小值数量就可以动态维护段数。

    然而要求的并不是段数，是原序列在每段的出现次数最大值的和。为了描述这个出现次数，
不妨再设一个辅助数组 {b} ，对于一个权值 w 和 x in S[w] ，令 b[x] = |S[w]| ，那么要求
的就是每段在 {b} 上的最大值的和，事实上，这样每个 w 涉及到的 b 的下标很多，可以仅令
b[min(S[w])] = |S[w]| ，这样在维护中可能更方便。

    使用线段树，维护 {a} 的最小值和最小值数的同时维护 {b} ，具体的，对于线段树的任意
一个节点，按 {a} 的最小值分段（不一定是 0 ），维护 {b} 在最左边一段的最大值，最右边
一段的最大值，整个区间的最大值，然后维护在每个段的最大值的和即可。稍加讨论可以发现这
些信息是可以 O(1) 合并的。

 * Digression:
  看上去很复杂，讨论清楚其实并不难，直接一遍过。

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
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 200005;
std::set<int> pos[maxn];
int min[maxn << 2], tot[maxn << 2], tag[maxn << 2];
int ans[maxn << 2], lv[maxn << 2], rv[maxn << 2], nv[maxn << 2];
#define ls (now << 1)
#define rs (now << 1 | 1)

void modi (int now, int x) {
	min[now] += x;
	tag[now] += x;
}

void push (int now) {
	if (tag[now]) {
		modi(ls, tag[now]);
		modi(rs, tag[now]);
		tag[now] = 0;
	}
}

void update (int now) {
	min[now] = std::min(min[ls], min[rs]);
	nv[now] = std::max(nv[ls], nv[rs]);
	if (min[ls] == min[rs]) {
		tot[now] = tot[ls] + tot[rs];
		ans[now] = ans[ls] + ans[rs] - rv[ls] - lv[rs] + std::max(rv[ls], lv[rs]);
		lv[now] = lv[ls];
		rv[now] = rv[rs];
	}
	if (min[ls] < min[rs]) {
		tot[now] = tot[ls];
		ans[now] = ans[ls] - rv[ls] + std::max(rv[ls], nv[rs]);
		lv[now] = lv[ls];
		rv[now] = std::max(rv[ls], nv[rs]);
	}
	if (min[ls] > min[rs]) {
		tot[now] = tot[rs];
		ans[now] = ans[rs] - lv[rs] + std::max(lv[rs], nv[ls]);
		lv[now] = std::max(lv[rs], nv[ls]);
		rv[now] = rv[rs];
	}
}

void modify (int now, int L, int R, int l, int r, int x) {
	if (r < L or l > R) return;
	if (l <= L and R <= r) return modi(now, x);
	int M = (L + R) >> 1;
	push(now);
	modify(ls, L, M, l, r, x);
	modify(rs, M + 1, R, l, r, x);
	update(now);
}

void modify2 (int now, int L, int R, int p, int x) {
	if (L == R) {
		ans[now] = lv[now] = nv[now] = x;
		return;
	}
	int M = (L + R) >> 1;
	push(now);
	if (p <= M) modify2(ls, L, M, p, x);
	else modify2(rs, M + 1, R, p, x);
	update(now);
}

void print (int now, int L, int R) {
	debug("%d - %d : l=%d r=%d n=%d a=%d\n",
			L, R, lv[now], rv[now], nv[now], ans[now]);
	if (L == R) return;
	int M = (L + R) >> 1;
	print(ls, L, M);
	print(rs, M + 1, R);
}

void build (int now, int L, int R) {
	tot[now] = R - L + 1;
	if (L == R) return;
	int M = (L + R) >> 1;
	build(ls, L, M);
	build(rs, M + 1, R);
}

int a[maxn];
void update (int w, int n, int x) {
	if (pos[w].empty()) return;
	int l = *pos[w].begin(), r = *pos[w].rbegin();
	if (l < r)
		modify(1, 1, n, l, r - 1, x);
	if (x == -1)
		modify2(1, 1, n, l, 0);
	if (x == 1)
		modify2(1, 1, n, l, int(pos[w].size()));
}

int main () {
	int n = read, q = read;
	for (int i = 1; i <= n; i ++)
		pos[a[i] = read].insert(i);
	build(1, 1, n);
	for (int w = 1; w <= 200000; w ++)
		update(w, n, 1);
	printf("%d\n", n - ans[1]);
	while (q --) {
		int p = read, w = read;
		update(a[p], n, -1);
		update(w, n, -1);
		pos[a[p]].erase(p);
		pos[w].insert(p);
		update(a[p], n, 1);
		update(w, n, 1);
		a[p] = w;
		printf("%d\n", n - ans[1]);
	}
	/* print(1, 1, n); */
}
