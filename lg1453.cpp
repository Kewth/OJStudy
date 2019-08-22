#if 0
2019.08.21

基环树模板，假设是树，设 f[u][0/1] 表示 u 点子树中是否选 u 点的最大收益即可。
考虑在环上计算答案？
有个很巧妙的处理方式，在环上随意选边 (u-v)，u 点和 v 点不可能同时选，
那么以 u, v 分别为根，计算出 f[u][0], f[v][0] 取最大值即可，
而且 dp 之前不需要删边，直接记 vis 当树 dp ，假设要算 f[u][0] ，
直接 dp 相当于断掉了与 u 相连的环边之一，
这样 dp 出来一定是对的，应为 dp 中钦定了 u 不选，那么即使断掉了这个限制关系也是对的。
#endif
#include <cstdio>
#include <vector>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1000005;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
int w[maxn];
lolong f[maxn][2];
bool vis[maxn];

void clear(int u) {
	vis[u] = false;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(vis[v])
			clear(v);
	}
}

int cx, cy;
bool find_circle(int u, int fa) {
	vis[u] = true;
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v != fa) {
			if(vis[v]) {
				cx = u;
				cy = v;
				return true;
			}
			if(find_circle(v, u))
				return true;
		}
	}
	return false;
}

void dp(int u) {
	vis[u] = true;
	f[u][0] = 0;
	f[u][1] = w[u];
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(not vis[v]) {
			dp(v);
			f[u][0] += std::max(f[v][0], f[v][1]);
			f[u][1] += f[v][0];
		}
	}
}

int main() {
	int n = input();
	assert(n < maxn);
	for(int u = 1; u <= n; u ++)
		w[u] = input();
	for(int i = 1; i <= n; i ++) {
		int u = input() + 1, v = input() + 1;
		assert(u != v);
		nxt[++ hp] = head[u];
		head[u] = hp;
		to[hp] = v;
		nxt[++ hp] = head[v];
		head[v] = hp;
		to[hp] = u;
	}
	double k;
	scanf("%lf", &k);
	lolong ans = 0;
	for(int i = 1; i <= n; i ++)
		if(not vis[i]) {
			if(find_circle(i, 0)) {
				clear(i);
				dp(cx);
				lolong fx = f[cx][0];
				clear(cx);
				dp(cy);
				lolong fy = f[cy][0];
				/* debug("%d:%lld %d:%lld\n", cx, fx, cy, fy); */
				ans += std::max(fx, fy);
			} else {
				dp(i);
				ans += std::max(f[i][0], f[i][1]);
			}
		}
	printf("%.1lf\n", ans * k);
}
