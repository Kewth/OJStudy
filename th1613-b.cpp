/*
 * Author: Kewth

 * Date:
  2021.05.31

 * Solution:
 * 可持久化平衡树，二分

  显然两个答案的两个维度互不影响且为等价的两个子问题。只考虑维护答案的 x 。

  假设只有操作 2 ，那么一次操作就是一次插入，用平衡树维护即可。

  而对于操作 1 ，同样用平衡树维护，假设询问的位置在第 i 次操作 1 上，那么相
当于只考虑第 i 次操作后的操作 2 的结果。也就是查询 x 之前有多少列是第 i 次操
作前产生的。容易想到树套树（划掉）。

  容易想到维护每个平衡树的历史版本，然后找到 x 在版本 i 上的节点查询 rank 。
但查 rank 要维护 fa ，而历史版本维护不了 fa ，仅能在最新版本上维护 fa 。那么
我们返璞归真，二分求 rank ，每次 check 就在版本 i 上查询 kth 然后回到最新版
本上查 rank 并与 x 比较。复杂度两个 log 。

  注意这里把二分放在平衡树上（出题人的做法）并不能优化复杂度（因为每个节点还
是要回最新版本查 rank），反而会使问题变复杂，要维护没必要的信息。

 * Digression:
  难度：7~8 / 12

  可持久化 Treap 如果要维护父亲节点，就只能在最新版本上维护，不可能对每个版
本维护。

  但其实这题还可以二进制分组做，复杂度不变，但常数很小。

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int K = 100000, maxq = 100005;

struct Treap {
	int lti, rti, fai;
	int size, weight, id;
} T[maxq * 60 + K * 4];
int tp;
#define _l T[now].lti
#define _r T[now].rti
#define _f T[now].fai
int newest[maxq + K * 4];

inline void update (int now) { T[now].size = T[_l].size + T[_r].size + 1; }

int version;
void split (int now, int k, int &a, int &b) {
	if (!now) return a = b = 0, void();
	if (version) {
		T[++ tp] = T[now];
		now = tp;
		T[_l].fai = T[_r].fai = now;
		newest[T[now].id] = now;
	}
	_f = 0;
	if (k <= T[_l].size)
		split(_l, k, a, _l), T[_l].fai = b = now;
	else
		split(_r, k - T[_l].size - 1, _r, b), T[_r].fai = a = now;
	update(now);
}

int merge (int a, int b) {
	if (!a) return b;
	if (!b) return a;
	int now;
	if (T[a].weight > T[b].weight)
		now = a, _r = merge(_r, b), T[_r].fai = now;
	else
		now = b, _l = merge(a, _l), T[_l].fai = now;
	update(now);
	return now;
}

// 只能在最新版本上查 rank
int rank (int now) {
	int res = 0, las = _r;
	while (now) {
		if (now != newest[T[now].id]) debug("ERROR\n"), exit(1);
		if (_r == las) res += T[_l].size + 1;
		las = now, now = _f;
	}
	return res;
}

int kth (int now, int k) {
	if (k <= T[_l].size) return kth(_l, k);
	if (k <= T[_l].size + 1) return now;
	return kth(_r, k - T[_l].size - 1);
}

int t1[maxq], t2[maxq];

int new_node (int id) {
	int now = ++ tp;
	T[now].size = 1;
	T[now].weight = rand();
	T[now].id = id;
	newest[id] = now;
	return now;
}

int main () {
	const int Max = 2 * K + 1;
	for (int i = 1; i <= Max; i ++)
		t1[0] = merge(t1[0], new_node(i));
	for (int i = Max + 1; i <= Max * 2; i ++)
		t2[0] = merge(t2[0], new_node(i));

	int Q = read, ansx = 0, ansy = 0, O = 1;
#ifdef LOCAL
	O = 0, debug("%d\n", Q);
#endif
	for (int q = 1; q <= Q; q ++) {
		version = q;
		int o = read;

		if (o == 1) {
			int k = read + K + 1 + (ansx + ansy) * O, a, b;
			int now = new_node(Max * 2 + q);
			split(t1[q - 1], k - 1, a, b);
			t1[q] = merge(a, merge(now, b));
			/* split(t1[q], Max, t1[q], b); */
			/* newest[T[b].id] = 0; */
			t2[q] = t2[q - 1];
#ifdef LOCAL
			debug("%d %d\n", o, k - K - 1 - ansx - ansy);
#endif
		}

		if (o == 2) {
			int k = read + K + 1 + (ansx + ansy) * O, a, b;
			int now = new_node(Max * 2 + q);
			split(t2[q - 1], k - 1, a, b);
			t2[q] = merge(a, merge(now, b));
			/* split(t2[q], Max, t2[q], b); */
			/* newest[T[b].id] = 0; */
			t1[q] = t1[q - 1];
#ifdef LOCAL
			debug("%d %d\n", o, k - K - 1 - ansx - ansy);
#endif
		}

		if (o == 3) {
			t1[q] = t1[q - 1], t2[q] = t2[q - 1];
			int x = read + K + 1 + (ansx + ansy) * O;
			int y = read + K + 1 + (ansx - ansy) * O;
			int nq, i;
#ifdef LOCAL
			debug("%d %d %d\n", o,
					x - K - 1 - ansx - ansy, y - K - 1 - ansx + ansy);
#endif

			nq = std::max(0, T[kth(t1[q], y)].id - Max * 2);
			i = T[kth(t2[q], x)].id;
			if (i > Max * 2 + nq)
				ansx = i - Max * 2;
			else {
				// 其实就是查 i 对应节点在 nq 版本的 rank ，妈的有没有简单方法啊
				int l = 1, r = Max;
				while (l < r) {
					int mid = (l + r + 1) >> 1;
					int node = newest[T[kth(t2[nq], mid)].id];
					if (node and rank(node) <= x) l = mid;
					else r = mid - 1;
				}
				ansx = l - K - 1;
			}

			nq = std::max(0, T[kth(t2[q], x)].id - Max * 2);
			i = T[kth(t1[q], y)].id;
			if (i > Max * 2 + nq)
				ansy = i - Max * 2;
			else {
				int l = 1, r = Max;
				while (l < r) {
					int mid = (l + r + 1) >> 1;
					int node = newest[T[kth(t1[nq], mid)].id];
					if (node and rank(node) <= y) l = mid;
					else r = mid - 1;
				}
				ansy = l - K - 1;
			}

			printf("%d %d\n", ansx, ansy);
		}
	}
}
