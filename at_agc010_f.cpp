#if 0
2019.08.13

将树按深度分层，不难发现每个点其实在开始就确定了只能被谁选。
换句话说，每个点的状态与从什么点开始无关。
再考虑一个权值为 x 的点移动到权值为 y 的点，
如果 y >= x ，那么对手的一个策略是重新回到 x ，
这时候仍有 x < y 但是 x 变小了，
如果一直向 y 走，最终 x 一定会变为 0 ，那就输了，
如果不向 y 走了，那么 x 变小了却没有赢得任何优势。

综上，每个点只会走向比自己小的点，
那么可以给边定向，然后直接 O(n) DP 出每个点的必胜必败态即可。
#endif
#include <cstdio>
#include <algorithm>

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 3030;
int head[maxn], nxt[maxn << 1], to[maxn << 1], hp;
bool vis[maxn], win[maxn];
int a[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
}

void dfs(int u) {
	vis[u] = true;
	for(int i = head[u]; i; i = nxt[i]) {
		if(not vis[to[i]])
			dfs(to[i]);
		if(not win[to[i]])
			win[u] = true;
	}
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	for(int i = 1; i < n; i ++) {
		int u = input(), v = input();
		if(a[u] > a[v])
			add(u, v);
		else if(a[u] < a[v])
			add(v, u);
	}
	for(int u = 1; u <= n; u ++)
		if(not vis[u])
			dfs(u);
	int last;
	for(int u = 1; u <= n; u ++)
		if(win[u])
			last = u;
	for(int u = 1; u <= n; u ++)
		if(win[u])
			printf("%d%c", u, " \n"[u == last]);
}
