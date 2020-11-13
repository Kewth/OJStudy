/*
 * Author: Kewth

 * Date:
  2020.11.10

 * Solution:
 * 问题转换，非常规树链剖分，线段树

  首先不妨把小于号的限制换成小于等于，容易证明对权值经过调整后这是个等价问题。

  进一步可以发现，对于一个点 u ，如果 p[u] = 0 ，那么其左儿子的值确定后 u 的权值的限制
就是他父亲和右儿子，而两者都要求 u 的权值足够小，因此 u 的权值只有两种可能：不修改，则
等于原值，修改，则等于左儿子的值。p[u] = 1 同理，u 的权值要么是原值要么是右儿子的值。

  据此我们搞一个树链剖分，若 p[u] = 0 则左儿子为重儿子，否则右儿子为重儿子。在这个树链
剖分的意义上可以设计一个 DP 设 f[u][x] 表示考虑 u 的子树，u 的权值最终为 x 的最小代价。
这里 x 的取值范围是 u 所在重链的点的原值。当然这样最坏情况仍是 O(n^2) 的。

  但是上述 DP 有较好的优化空间，转移的时候考虑从重儿子继承 DP 数组，然后枚举轻儿子所在
重链上的每个点算贡献，那么每个点影响的都是 x 的一段区间。这样一来可以用线段树维护一条
重链的 DP 数组，需要支持的操作无非是区间加，区间求 min ，单点取 min （采用原值时）。而
枚举轻儿子所在重链这一步中显然每个点被枚举至多一次。因此总复杂度是 O(nlog) 的。

 * Digression:
  我自闭了。

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
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 500005, inf = 1000000000;
int a[maxn];
int fa[maxn], flag[maxn], son[maxn][2];
int list[maxn], lp;
int tmp[maxn];

void predfs (int u, int f) {
	if (!u) return;
	a[u] += f;
	predfs(son[u][0], f + 1);
	/* debug("%d\n", a[u]); */
	predfs(son[u][1], f - 1);
}

struct Seg {
	int *min, *tag, n, fuck;
	std::vector<par> Res;
	inline void ad (int now, int x) { min[now] += x, tag[now] += x; }
	inline void push (int now) {
		if (tag[now])
			ad(now << 1, tag[now]), ad(now << 1 | 1, tag[now]), tag[now] = 0;
	}
	inline void U (int p, int x) { int y = Q(p, p); if (x < y) A(p, p, x - y); }
	void add (int now, int L, int R, int l, int r, int x) {
		if (R < l or L > r) return;
		/* debug("add %d %d %d\n", L, R, x); */
		if (l <= L and R <= r) return ad(now, x);
		push(now);
		int M = (L + R) >> 1;
		add(now << 1, L, M, l, r, x);
		add(now << 1 | 1, M + 1, R, l, r, x);
		min[now] = std::min(min[now << 1], min[now << 1 | 1]);
	}
	inline void A (int l, int r, int x) { if (l <= r) add(1, 1, n, l, r, x); }
	int query (int now, int L, int R, int l, int r) {
		if (R < l or L > r) return inf + inf; // XXX: 啊这我自闭了
		/* debug("query %d %d (%d %d)\n", L, R, min[now], tag[now]); */
		if (l <= L and R <= r) return min[now];
		push(now);
		int M = (L + R) >> 1;
		return std::min(query(now << 1, L, M, l, r),
				query(now << 1 | 1, M + 1, R, l, r)) + tag[now];
	}
	inline int Q (int l, int r) { return query(1, 1, n, l, r); }
	void init (int N) {
		n = N;
		min = new int[unsigned(n * 4)];
		tag = new int[unsigned(n * 4)];
		std::fill(min, min + n * 4, inf);
		std::fill(tag, tag + n * 4, 0);
	}
	void get (int o) {
		Res.clear();
		for (int i = 1; i <= n; i ++)
			Res.push_back(par(tmp[i], o == 0 ? Q(1, i) : Q(i, n)));
	}
} seg[maxn];

void dfs (int u) {
	if (!u) return;
	int o = flag[u], *lis = list + lp, tot = 0, tp = 0;
	for (int x = u; x; x = son[x][o])
		lis[++ tot] = x;
	lp += tot;
	for (int x = u; x; x = son[x][o])
		dfs(son[x][!o]);
	for (int x = u; x; x = son[x][o])
		tmp[++ tp] = a[x];
	if (o == 0) tmp[++ tp] = - inf;
	if (o == 1) tmp[++ tp] = + inf;
	std::sort(tmp + 1, tmp + tp + 1);
	seg[u].init(tp = int(std::unique(tmp + 1, tmp + tp + 1) - tmp - 1));
	auto &S = seg[u];
	/* debug("solve %d\n", u); */
	if (o == 0) S.U(1, 0);
	if (o == 1) S.U(tp, 0);
	for (int i = tot; i; i --) {
		int x = lis[i], ax = int(std::lower_bound(tmp + 1, tmp + tp + 1, a[x]) - tmp);
		/* debug(" >> %d\n", x); */
		if (o == 0) {
			int now = S.Q(1, ax);
			if (son[x][!o]) {
				auto &V = seg[son[x][!o]].Res;
				auto it = std::lower_bound(V.begin(), V.end(), par(a[x], 0));
				now += it -> second;
				int begin = 1;
				for (par p : V) {
					int ti = int(std::upper_bound(tmp + 1,
								tmp + tp + 1, p.first) - tmp - 1);
					S.A(begin, ti, p.second);
					begin = ti + 1;
				}
			}
			S.A(1, tp, 1);
			S.U(ax, now);
		}
		if (o == 1) {
			int now = S.Q(ax, tp);
			if (son[x][!o]) {
				auto &V = seg[son[x][!o]].Res;
				auto it = std::upper_bound(V.begin(), V.end(), par(a[x], inf)) - 1;
				now += it -> second;
				int begin = tp;
				std::reverse(V.begin(), V.end());
				for (par p : V) {
					int ti = int(std::lower_bound(tmp + 1,
								tmp + tp + 1, p.first) - tmp);
					S.A(ti, begin, p.second);
					begin = ti - 1;
				}
			}
			S.A(1, tp, 1);
			S.U(ax, now);
		}
		/* for (int k = 1; k <= tp; k ++) */
		/* 	debug("%d %d\n", tmp[k], S.Q(k, k)); */
	}
	S.get(o);
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	for (int u = 2; u <= n; u ++) {
		read(fa[u], flag[u]);
		son[fa[u]][flag[u]] = u;
	}
	predfs(1, 0);
	dfs(1);
	printf("%d\n", seg[1].Res.back().second);
}
