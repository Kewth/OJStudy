#include <bits/stdc++.h>

const int nmax = 1000, mmax = 1000;
const int maxn = nmax+nmax+nmax+2;
const int maxm = nmax*2+mmax*nmax*2;
const int inf = 2000000001;
int head[maxn], Head[maxn], level[maxn];
int nxt[maxm<<1], to[maxm<<1], cap[maxm<<1], p = 1;

void add(int x, int y, int c) {
	nxt[++p] = head[x];
	head[x] = p;
	to[p] = y;
	cap[p] = c;
	nxt[++p] = head[y];
	head[y] = p;
	to[p] = x;
	cap[p] = 0;
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
			if(not level[v] and cap[i]) {
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
			int cc = dfs(v, t, std::min(cap[i], c));
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

int main(const int, const char**) {
	std::ios::sync_with_stdio(false);
	int n, m, ans = 0;
	std::cin >> n;
	int s = 0, t = n + 1;
	for(int i=1;i<=n;i++) {
		int a;
		std::cin >> a;
		add(s, i, a);
		ans += a;
	}
	for(int i=1;i<=n;i++) {
		int b;
		std::cin >> b;
		add(i, t, b);
		ans += b;
	}
	std::cin >> m;
	for(int i=1;i<=m;i++) {
		int sl, a, b;
		std::cin >> sl >> a >> b;
		add(s, t-1+(i<<1), a);
		add(t+(i<<1), t, b);
		for(int j=1;j<=sl;j++) {
			int k;
			std::cin >> k;
			add(t-1+(i<<1), k, inf);
			add(k, t+(i<<1), inf);
		}
		ans += a + b;
	}
	std::cerr << ans << std::endl;
	ans -= max_flow(s, t);
	std::cout << ans << std::endl;
}
