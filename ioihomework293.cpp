/*
 * Author: Kewth

 * Date:
  2020.10.31

 * Solution:
  把所有 4^n 种情况的编码建 Trie ，由于编码之间两两没有前缀关系，那么 Trie 的单词节点
两两没有祖先关系。一个 Trie 的期望代价就是每个叶子的权值乘上其深度的和。
  而最小化这个 Trie 的期望代价是很简单的，每次贪心选两个最小的叶子合并即可。
  唯一的问题在于节点数 4^n 太多，不过许多都是权值相同的，爆搜四种天气的数量，用组合数
算一类权值的节点的数量，将它们作为整体应用到贪心算法即可。

 * Digression:
  这个最优编码就是 Huffman 编码，上文的 Trie 树就是 Huffman 树，上文的贪心算法就是构
建 Huffman 树的一个常用算法。

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;
typedef std::pair<ld, ll> par;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ld () { ld x; return scanf("%Lf", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 21;
ld a[maxn], b[maxn], c[maxn], d[maxn];
ll fac[maxn];

int main () {
	int n = read;
	a[0] = b[0] = c[0] = d[0] = 1;
	read(a[1], b[1], c[1], d[1]);
	fac[0] = fac[1] = 1;
	for (int i = 2; i <= n; i ++) {
		a[i] = a[i - 1] * a[1];
		b[i] = b[i - 1] * b[1];
		c[i] = c[i - 1] * c[1];
		d[i] = d[i - 1] * d[1];
		fac[i] = fac[i - 1] * i;
	}

	std::priority_queue<par, std::vector<par>, std::greater<par>> q;
	ld ans = 0;
	auto push = [&] (ld p, ll t, bool add = 0) -> void {
		if (!t) return;
		if (add) ans += p * t;
		q.push(par(p, t));
		/* debug("push %Lf %lld\n", p, t); */
	};

	for (int ai = 0; ai <= n; ai ++)
		for (int bi = 0; bi <= n; bi ++)
			for (int ci = 0; ci <= n; ci ++)
				for (int di = 0; di <= n; di ++)
					if (ai + bi + ci + di == n) {
						ld p = a[ai] * b[bi] * c[ci] * d[di];
						ll t = fac[n] / fac[ai] / fac[bi] / fac[ci] / fac[di];
						/* ans += p * std::log2(1 / p) * t; */
						/* debug("%d %d %d %d %Lf %lld\n", ai, bi, ci, di, p, t); */
						push(p, t);
					}

	while (1) {
		par p = q.top(); q.pop();
		/* debug("> %Lf %lld\n", p.first, p.second); */
		push(p.first * 2, p.second / 2, true);
		if (p.second & 1) {
			if (q.empty()) break;
			par p2 = q.top(); q.pop();
			/* debug(">> %Lf %lld\n", p2.first, p2.second); */
			push(p.first + p2.first, 1, true);
			push(p2.first, p2.second - 1);
		}
	}

	printf("%Lf\n", ans);
}
