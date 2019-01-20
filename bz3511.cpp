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
	std::cerr << ans << std::endl;
	std::cout << ans - max_flow(s, t) << std::endl;
}
