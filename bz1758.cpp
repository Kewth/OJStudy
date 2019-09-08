#if 0
2019.09.03

分数规划，先二分答案，然后问题转换为回答是否存在长度在 [L, R] 内的权值非负的路径。
暴力 DP 设 F[u][x] 表示 u 子树内以 u 为一端长度为 x 的权值最大路径。
每次转移中子树合并时可以更新答案。

这个 DP 的第二维只与深度有关，改一下定义 f[u][x] 表示 u 子树内深度与 u 差 x 的最大 dis 。
这个问题可以用长链剖分 O(n) 计算，然后不难发现有 F[u][x] = f[u][x] - dis[u] 。

现在的问题是优化更新答案的部分，暴力枚举更新的复杂度仍然是 O(n^2) 的。
考虑枚举轻儿子 v 更新答案的过程，对于每个 f[v][x] 只有 f[u][L - x ~ R - x] 可以对应贡献。
用线段树维护 f ，那么枚举每个 f[v][x] 对应的就是一个区间最值查询。
合并轻儿子 v 的信息的时候枚举 f[v][x] 加入到 f[u][x] （取 max ）即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
int id[maxn], len[maxn], son[maxn], ip;
int num[maxn];
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
lolong dis[maxn];
lolong val[maxn << 1];
lolong f[maxn * 3];

inline void add(int u, int v, lolong w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	val[hp] = w;
}

void dfs(int u, int fa) {
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa) {
			dfs(to[i], u);
			if(len[to[i]] > len[son[u]])
				son[u] = to[i];
		}
	len[u] = len[son[u]] + 1;
}

int modify(int now, int L, int R, int p, lolong x) {
	f[now] = std::max(f[now], x);
	if(L == R)
		return now;
	int mid = (L + R) >> 1;
	if(p <= mid)
		return modify(now << 1, L, mid, p, x);
	else
		return modify(now << 1 | 1, mid + 1, R, p, x);
}

lolong query(int now, int L, int R, int l, int r) {
	if(l > r or r < L or l > R)
		return - 1000000000000000ll;
	if(l <= L and R <= r)
		return f[now];
	int mid = (L + R) >> 1;
	return std::max(query(now << 1, L, mid, l, r),
			query(now << 1 | 1, mid + 1, R, l, r));
}

void clear(int now, int L, int R) {
	f[now] = - 1000000000000000ll;
	if(L == R)
		return;
	int mid = (L + R) >> 1;
	clear(now << 1, L, mid);
	clear(now << 1 | 1, mid + 1, R);
}

lolong ans;
int n, L, R;

void dp(int u, int fa) {
	id[u] = ++ ip;
	num[id[u]] = modify(1, 1, n, id[u], dis[u]);

	/* debug("%d id-> %d\n", u, id[u]); */

	if(son[u])
		for(int i = head[u]; i; i = nxt[i])
			if(to[i] == son[u]) {
				id[to[i]] = id[u] + 1;
				dis[to[i]] = dis[u] + val[i];
				dp(to[i], u);
			}

	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != fa and to[i] != son[u]) {
			id[to[i]] = id[u] + len[u];
			dis[to[i]] = dis[u] + val[i];

			dp(to[i], u);

			for(int j = 0; j < len[to[i]]; j ++)
				ans = std::max(ans,
						f[num[id[to[i]] + j]] +
						query(1, 1, n,
							id[u] + std::max(L - j - 1, 0),
							id[u] + std::min(R - j - 1, len[u] - 1)) -
						dis[u] * 2);

			for(int j = 0; j < len[to[i]]; j ++)
				modify(1, 1, n, id[u] + j + 1, f[num[id[to[i]] + j]]);
		}

	ans = std::max(ans,
			query(1, 1, n,
				id[u] + std::max(L, 0),
				id[u] + std::min(R, len[u] - 1)) - dis[u]);
}

int main() {
	n = input();
	L = input();
	R = input();

	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		lolong w = 1ll * input() * 10000;
		add(u, v, w);
		add(v, u, w);
	}

	dfs(1, 0);

	lolong l = 0, r = 10000000000ll;
	while(l < r) {
		lolong mid = (l + r + 1) >> 1;

		clear(1, 1, n);

		for(int i = 1; i <= hp; i ++)
			val[i] -= mid;

		ans = - 1000000000000000ll;

		ip = 0;
		dp(1, 0);

		/* debug("%lld : %lld\n", mid, ans); */

		if(ans >= 0)
			l = mid;
		else
			r = mid - 1;

		for(int i = 1; i <= hp; i ++)
			val[i] += mid;
	}

	printf("%.3lf\n", l * 0.0001);
}
