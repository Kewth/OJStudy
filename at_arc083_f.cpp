#if 0
2019.12.12

有点恶心。

每个机器人看做一个点，平面上的每个点看做连接机器人的边。
形成的图一定是基环树森林，否则说明有一行或一列为空，直接输出 0 。

单独考虑森林的每一颗基环树，每个机器人要认领一个平面上的点，
相当于每个点要认领一条边。
树上认领边的方向是唯一的，只有环上的点有两种认领可能，枚举这两种认领方向。
然后机器人走到的点已经确定，考虑计算有多少顺序。

注意到机器人 (x, 0) -> (x, y) 的顺序限制在于对于满足 y0 < y 的 (x, y0) ，
到 (x, y0) 的机器人 (0, y0) 需要在 (x, 0) 之前启动，
对于这个限制关系再次建图，如果建出来有环，全局无解，输出 0 。
否则一定是一个 DAG ，事实上由于点数大于边数，它是颗树，
合法的顺序对应该树的一个拓扑序，树形 DP 求出拓扑序数量即可。

总的答案串一串，简单组合排列一下即可，略去。

细节巨多。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 400005, mod = 1000000007;
int head[maxn], nxt[maxn << 2], to[maxn << 2], hp = 1;

inline ll power(ll x, int k) {
	if(k < 0) k += mod - 1;
	ll res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

inline void add(int u, int v, int *h) {
	nxt[++ hp] = h[u];
	h[u] = hp;
	to[hp] = v;
}

int tmp[maxn], tp;
bool vis[maxn];
int cx, cy;
int dfs(int u, int f) {
	/* debug("%d -> %d\n", f, u); */
	tmp[++ tp] = u;
	vis[u] = 1;
	int res = 0;

	for(int i = head[u]; i; i = nxt[i], ++ res)
		if(to[i] != f) {
			if(vis[to[i]]) {
				cx = u;
				cy = to[i];
			} else
				res += dfs(to[i], u);
		}

	/* debug("dfs %d %d\n", u, res); */

	return res;
}

int match[maxn];
void mdfs(int u, int f) {
	/* debug("%d -> %d\n", f, u); */
	for(int i = head[u]; i; i = nxt[i])
		if(to[i] != f and to[i] != cx) {
			match[to[i]] = u;
			mdfs(to[i], u);
		}
}

int Head[maxn];
int deg[maxn];
int stack[maxn], sp;
ll f[maxn];
int size[maxn];
ll fac[maxn], ifac[maxn];

inline ll C(int n, int m) {
	return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}

int force_count;
void dp(int u) {
	++ force_count;
	if(force_count >= maxn * 2) {
		puts("0");
		exit(0);
	}

	size[u] = 0;
	f[u] = 1;
	for(int i = Head[u]; i; i = nxt[i]) {
		dp(to[i]);
		size[u] += size[to[i]];
		(f[u] *= f[to[i]]) %= mod;
		(f[u] *= C(size[u], size[to[i]])) %= mod;
	}
	++ size[u];
	debug("%d : %lld %d\n", u, f[u], size[u]);
}

int HP;
ll solve() {
	debug("solve %d %d\n", cx, cy);
	mdfs(cx, cy);
	match[cx] = cy;

	hp = HP;
	for(int i = 1; i <= tp; i ++)
		deg[tmp[i]] = Head[tmp[i]] = 0;

	for(int id = 1; id <= tp; id ++) {
		int u = tmp[id];
		for(int i = head[u]; i; i = nxt[i])
			if(to[i] < match[u]) {
				debug("%d -> %d\n", u, to[i]);
				add(u, to[i], Head);
				++ deg[to[i]];
			}
	}

	Head[0] = 0;
	for(int i = 1; i <= tp; i ++)
		if(!deg[tmp[i]])
			add(0, tmp[i], Head);

	dp(0);
	debug("get %lld\n", f[0]);

	return f[0];
}

int main() {
	int n = read;

	int N = n << 1 | 1;
	fac[0] = 1;
	for(int i = 1; i <= N; i ++)
		fac[i] = fac[i - 1] * i % mod;
	ifac[N] = power(fac[N], -1);
	for(int i = N; i; i --)
		ifac[i - 1] = ifac[i] * i % mod;

	for(int i = 1; i < N; i ++) {
		int x = read, y = read;
		add(x, n + y, head);
		add(n + y, x, head);
	}

	HP = hp;
	ll ans = 1;
	int SIZE = 0;

	for(int r = 1; r < N; r ++)
		if(!vis[r]) {
			tp = 0;
			if(dfs(r, 0) != (tp << 1)) return puts("0"), 0;
			ll now = solve();
			std::swap(cx, cy);
			now += solve();
			SIZE += size[0] - 1;
			(ans *= now) %= mod;
			(ans *= C(SIZE, size[0] - 1)) %= mod;
		}

	printf("%lld\n", ans);
}
