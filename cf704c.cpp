#if 0
2020.02.03

把式子看作点，对于一个元素，如果出现恰好两次，看作一条边，
如果出现恰好一次，新增式子 x | 1 ，仍然将 x 看作边，连向这个新式子。
注意即使没有出现过也会对答案有 2 倍的贡献。

由于每个元素有两个取值，每条边也有两种状态，
可以发现边有两种，一种是边的状态表示是否同时另两个端点为 1 ，
一种是边的状态表示在两个端点中选一个端点为 1 。

每个点的度数不超过 2 ，因此每个联通块不是链就是环，
对于每个联通块 DP 求出该联通块异或和为 0/1 的方案数，
然后再用 DP 合并所有联通块得到整张图异或和为 0/1 的方案数。

需要注意的是新增的式子可以转移，但不能被算入实际的异或和中。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 100005, mod = 1000000007;
int a[maxn], b[maxn];
int head[maxn << 1], nxt[maxn << 1], to[maxn << 1], typ[maxn << 1], hp = 1;
bool spec[maxn];

inline void add(int u, int v, int t) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	typ[hp] = t;
}

struct DP {
	int f[2][2][2];
	DP trans(int t) {
		DP n;
		if(t == 0)
			for(int o = 0; o < 2; o ++) {
				n.f[0][0][o] = (f[0][0][o] + f[0][1][o ^ 1]) % mod;
				n.f[1][0][o] = (f[1][0][o] + f[1][1][o ^ 1]) % mod;
				n.f[0][1][o] = (f[0][0][o ^ 1] + f[0][1][o ^ 1]) % mod;
				n.f[1][1][o] = (f[1][0][o ^ 1] + f[1][1][o ^ 1]) % mod;
			}
		if(t == 1)
			for(int o = 0; o < 2; o ++) {
				n.f[0][0][o] = (f[0][0][o ^ 1] + f[0][1][o]) % mod;
				n.f[1][0][o] = (f[1][0][o ^ 1] + f[1][1][o]) % mod;
				n.f[0][1][o] = (f[0][0][o ^ 1] + f[0][1][o ^ 1]) % mod;
				n.f[1][1][o] = (f[1][0][o ^ 1] + f[1][1][o ^ 1]) % mod;
			}
		return n;
	}
};

DP make() {
	DP n;
	memset(n.f, 0, sizeof n.f);
	n.f[0][0][0] = 1;
	n.f[0][1][1] = 1;
	n.f[1][0][1] = 1;
	n.f[1][1][1] = 1;
	return n;
}

bool vis[maxn << 1];
DP df;
int dfs(int u) {
#if 0
	debug("f[%d]:", u);
	for(int i = 0; i < 4; i ++)
		debug(" %d %d |", df.f[i >> 1][i & 1][0], df.f[i >> 1][i & 1][1]);
	debug("\n");
#endif

	vis[u] = 1;
	for(int i = head[u]; i; i = nxt[i])
		if(!vis[to[i]]) {
			df = df.trans(typ[i]);
			return dfs(to[i]);
		}
	return u;
}

int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++) {
		int t = read;
		while(t --) {
			int x = read, o = 1;
			if(x < 0) {
				x = -x;
				o = -1;
			}
			if(!a[x]) a[x] = i * o;
			else b[x] = i * o;
		}
	}

	ll ans[2] = {1, 0};
	int np = n;
	for(int i = 1; i <= m; i ++)
		if(a[i]) {
			if(!b[i])
				b[i] = ++ np;
			int oa = a[i] > 0 ? 1 : -1;
			int ob = b[i] > 0 ? 1 : -1;
			// debug("%d %d\n", a[i], b[i]);
			add(a[i] * oa, b[i] * ob, oa != ob);
			add(b[i] * ob, a[i] * oa, oa != ob);
		} else
			(ans[0] <<= 1) %= mod;

	for(int i = 1; i <= np; i ++)
		if(!vis[i] and !nxt[head[i]]) {
			df = make();
			int j = dfs(i);
			auto g = df.f[i > n][j > n];

			ll tmp[2] = {ans[0], ans[1]};
			ans[0] = (tmp[0] * g[0] + tmp[1] * g[1]) % mod;
			ans[1] = (tmp[0] * g[1] + tmp[1] * g[0]) % mod;

			if((i > n) != (j > n))
				std::swap(ans[0], ans[1]);

			// debug("(%d %d) -> %lld %lld\n", i, j, ans[0], ans[1]);
		}

	for(int i = 1; i <= n; i ++)
		if(!vis[i]) {
			df = make();
			dfs(i);
			int t = typ[nxt[head[i]]];
			int g[2] = {df.f[0][t][0] + df.f[1][!t][0],
				df.f[0][t][1] + df.f[1][!t][1]};

			ll tmp[2] = {ans[0], ans[1]};
			ans[0] = (tmp[0] * g[0] + tmp[1] * g[1]) % mod;
			ans[1] = (tmp[0] * g[1] + tmp[1] * g[0]) % mod;
		}

	printf("%lld\n", ans[1]);
}
