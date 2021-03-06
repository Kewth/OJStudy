#include <bits/stdc++.h>
// template {{{1
const int maxn = 1005, maxm = 1005*1005*2;
const int inf = 1000000000;
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

long long max_flow(int s, int t) {
	long long res = 0;
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

// Global definition {{{1
int use[maxn], know[maxn][maxn];

// Main function {{{1
int main(const int, const char **) {
	std::ios::sync_with_stdio(false);
	int n;
	std::cin >> n;
	int S = 0, T = n + 1;
	long long ans = 0;
	for(int i=1;i<=n;i++)
		std::cin >> use[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) {
			std::cin >> know[i][j];
			ans += know[i][j];
		}
	for(int i=1;i<=n;i++) {
		add(S, i, use[i]);
		/* add(i, T, use[i]); */
		int sum = 0;
		for(int j=1;j<=n;j++)
			if(i != j)
				sum += know[j][i];
		add(i, T, sum);
		/* add(S, i, sum); */
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i != j)
				add(i, j, know[i][j] << 1);
	std::cerr << "SUM !" << ans << std::endl;
	ans -= max_flow(S, T);
	std::cout << ans << std::endl;
}

// {{{1
// }}}1
