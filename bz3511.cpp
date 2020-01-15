#if 0
2019.01.20

先获得所有收益，用最小割求出舍弃的最小收益，即得出最大收益。
考虑建图，首先每个点与 s, t 连边，流量分别为选 a, b 的收益，即可保证必须舍弃一个。
其次，对于每条边 (u, v EA, EB, EC)，
本来一 A 一 B 要有 EA + EB + EC 的代价，那么 u, v 相互连 EA + EB + EC 的边，
然而考虑到两 A 或两 B 的情况分别也有 EB 或 EA 的代价，发现这个代价难以用边表示。
很妙的做法是根据 u 的颜色讨论，u 选 A 的话，v 选 A, B 的代价分别是 EB, EA + EB + EC ，
那么直接令 u 选 A 的代价为 EB （与 s 连边），u, v 之间就只需连 EB + EC 的边表示代价。
u 选 B 的情况类似，继续连边即可。
#endif
#include <bits/stdc++.h>

const int maxn = 90000, maxm = 300000;
const int inf = 2000000000;
int head[maxn], Head[maxn], level[maxn];
int nxt[maxm<<1], to[maxm<<1], cap[maxm<<1], p = 1;

void add(int x, int y, int c, bool two) {
	nxt[++p] = head[x];
	head[x] = p;
	to[p] = y;
	cap[p] = c;
	nxt[++p] = head[y];
	head[y] = p;
	to[p] = x;
	cap[p] = two ? c : 0;
}

bool bfs(int s, int t) {
	std::queue<int> q;
	q.push(s);
	memset(level, 0, sizeof(level));
	level[s] = 1;
	while(not q.empty()) {
		int u = q.front();
		q.pop();
		for(int i=head[u];i;i=nxt[i]) {
			int v = to[i];
			if(cap[i] and not level[v]) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return level[t];
}

int dfs(int u, int t, int c) {
	if(u == t)
		return c;
	for(int &i=Head[u];i;i=nxt[i]) {
		int v = to[i];
		if(cap[i] and level[v] == level[u] + 1) {
			int cc = dfs(v, t, std::min(c, cap[i]));
			if(cc) {
				cap[i] -= cc;
				cap[i^1] += cc;
				return cc;
			}
		}
	}
	return 0;
}

int max_flow(int s, int t) {
	int res = 0;
	while(bfs(s, t)) {
		memcpy(Head, head, sizeof(Head));
		int now = 0;
		do {
			now = dfs(s, t, inf);
			res += now;
		} while(now);
	}
	return res;
}

int main(int, char **) {
	std::ios::sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;
	int s = 0, t = n + 1;
	int ans = 0;
	for(int i=2;i<n;i++) {
		int a;
		std::cin >> a;
		ans += a;
		add(s, i, a, false);
	}
	add(s, 1, inf, false);
	for(int i=2;i<n;i++) {
		int b;
		std::cin >> b;
		ans += b;
		add(i, t, b, false);
	}
	add(n, t, inf, false);
	for(int i=1;i<=m;i++) {
		int x, y, a, b, c;
		std::cin >> x >> y >> a >> b >> c;
		ans += a + b;
		/* add(s, n + i*2, a, false); */
		/* add(n + i*2, x, inf, false); */
		/* add(n + i*2, y, inf, false); */
		/* add(x, n + i*2 + 1, inf, false); */
		/* add(y, n + i*2 + 1, inf, false); */
		/* add(n + i*2 + 1, t, b, false); */
		/* add(x, y, c, true); */
		add(x, y, b + c, false);
		add(y, x, a + c, false);
		add(s, y, a, false);
		add(y, t, b, false);
	}
	/* std::cerr << ans << std::endl; */
	std::cout << ans - max_flow(s, t) << std::endl;
}
