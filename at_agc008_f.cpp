#if 0
2019.12.17

假设所有点都是关键点，记 f(u, k) 表示集合 {x | dis(u, x) < k} 。
问题相当于求所有本质不同的 f(u, k) 数量。

点的全集比较特殊，单独考虑。
对于点 u ，设其作为根时的树深度为 d ，那么满足 k < d 的 f(u, k) 都可以被计入答案。
但是这样会算重，因为存在 f(u, k1) = f(v, k2) 且 u != v 。
对于每个可行的点集，能表示出来的 f(u, k) 中一定存在一个 k 最小的唯一的 u ，
如果仅在 k 最小的 u 上统计该点集就不会算重，

考虑每个 f(u, k) 的 k 需要满足什么条件才能满足上述条件，
设 u 的深度最大的儿子为 v ，如果 f(v, k - 1) = f(u, k) 那么 k 不可行，
也就是说 k 还需要满足 k - 1 <= d2 ，其中 d2 是除去 v 子树后的树深度。
综上，答案为 1 + sum(min(d - 1, d2 + 1)) 。

现在考虑存在非关键点的情况。
一个 naive 的想法是只对关键点统计上述贡献，
但可能有一个合法点集应在 f(u, k) 处被统计，而 u 现在成了非关键点，这样就漏记了。

考虑非关键点 u 作为根时，k 要额外满足什么条件才能统计 f(u, k) 。
事实上当 f(u, k) 包含了任一包含关键点的 v 的子树时才能被统计，其中 v 是 u 的儿子。
也就是说需要满足 k >= bd ，其中 bd 是所有包含关键点的 v 子树的深度的最小值。

实现时只需要用换根 DP 求出每个点作为根时的 d, d2, bd 即可，
辅助转移需要记 c 表示子树内关键点的数量。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 200005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
char s[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

struct Data {
	int d, d2, bd, c;

	inline void update(Data an) {
		if(an.d + 1 > d) {
			d2 = d;
			d = an.d + 1;
		} else
			d2 = std::max(d2, an.d + 1);
		if(an.c)
			bd = std::min(bd, an.d);
		c += an.c;
	}

	inline void undo(Data an) { // only need "d" and "c" to update
		if(an.d + 1 == d)
			d = d2;
		c -= an.c;
	}
};
Data f[maxn];

void dfs1(int u, int fa) {
	f[u] = {1, 1, maxn, s[u] == '1'};

	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v != fa) {
			dfs1(v, u);
			f[u].update(f[v]);
		}
	}

	/* debug("%d : %d %d %d\n", u, f[u].d, f[u].d2, f[u].bd); */
}

ll ans = 1;
void dfs2(int u, int fa, Data ff) {
	Data g = f[u];
	g.update(ff);

	int L = s[u] == '1' ? 1 : g.bd + 1;
	int R = std::min(g.d - 1, g.d2 + 1);
	if(L <= R) ans += R - L + 1;

/* 	debug("%d : %d %d %d\n", u, g.d, g.d2, g.bd); */
/* 	debug("from %d %d\n", ff.d, ff.bd); */
/* 	debug("ans %d-%d\n", L, R); */

	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v != fa) {
			Data vff = g;
			vff.undo(f[v]);
			dfs2(v, u, vff);
		}
	}
}

int main() {
	int n = read;
	for(int i = 1; i < n; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}
	scanf("%s", s + 1);

	dfs1(1, 0);
	dfs2(1, 0, {0, 0, maxn, 0});

	printf("%lld\n", ans);
}
