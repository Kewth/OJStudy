#if 0
2019.12.17

对每个 (a, b) 连有向边，单独考虑每个联通块。
将联通块染色，染三种颜色 1, 2, 3 ，设点 u 颜色为 c[u] ，
需要满足对于任意 a -> b 有 c[b] = f(c[a]), f(1, 2, 3) = (2, 3, 1) 。

1) 如果不能成功染色，那么整个联通块最后会成为完全图且每个点有自环。
证明不会。
2) 如果只能染出一种或两种颜色，那么整个联通块无法扩展出新边。
可以反证。
3) 如果能成功染出三种颜色，那么颜色 x 和颜色 f(x) 之间的点最后会两两连有向边。
证明不会，不过大概是和 1) 一个道理。

据此就可以通过染色结果计算出整张图最后的边数了。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp = 1;
int color[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

bool fuck;
int tot[4];
void dfs(int u, int c) {
	if(c > 3) c -= 3;
	if(color[u] and color[u] != c) return fuck = 1, void();
	if(color[u]) return;

	++ tot[color[u] = c];
	for(int i = head[u]; i; i = nxt[i]) {
		if(i & 1)
			dfs(to[i], c + 2);
		else {
			dfs(to[i], c + 1);
			++ tot[0];
		}
	}
}

inline ll sq(ll x) { return x * x; }

int main() {
	int n = read, m = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		add(u, v);
		add(v, u);
	}

	ll ans = 0;
	for(int i = 1; i <= n; i ++)
		if(!color[i]) {
			fuck = tot[0] = tot[1] = tot[2] = tot[3] = 0;
			dfs(i, 1);
			/* debug("%d %d %d %d %d\n", fuck, tot[0], tot[1], tot[2], tot[3]); */
			if(fuck)
				ans += sq(tot[1] + tot[2] + tot[3]);
			else if(!tot[1] or !tot[2] or !tot[3])
				ans += tot[0];
			else
				ans += 1ll * tot[1] * tot[2] + 1ll * tot[2] * tot[3] + 1ll * tot[3] * tot[1];
		}

	printf("%lld\n", ans);
}
