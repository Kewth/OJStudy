#include <bits/stdc++.h>

const int maxn = 202, maxm = 202*102;
const int inf = 1000000000;
int head[maxn], match[maxn];
int nxt[maxm], to[maxm], p = 0;
int dist[maxn][maxn];
bool in[maxn];

void add(int x, int y) {
	/* std::cerr << x << "link" << y << std::endl; */
	nxt[++p] = head[x];
	head[x] = p;
	to[p] = y;
	nxt[++p] = head[y];
	head[y] = p;
	to[p] = x;
}

void floyd(int n) {
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dist[i][j] = std::min(dist[i][k] + dist[k][j], dist[i][j]);
}

bool dfs(int u) {
	for(int i=head[u];i;i=nxt[i]) {
		int v = to[i];
		if(in[v]) continue;
		in[v] = true;
		if(not match[v] or dfs(match[v])) {
			match[u] = v;
			match[v] = u;
			return true;
		}
	}
	return false;
}

int hungrian(int n) {
	int res = 0;
	for(int i=1;i<=n;i++)
		if(not match[i]) {
			memset(in, 0, sizeof(in));
			res += dfs(i);
		}
	return res;
}

int main(int, char **) {
	std::ios::sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dist[i][j] = inf;
	for(int i=1;i<=m;i++) {
		int a, b;
		std::cin >> a >> b;
		dist[a][b] = 1;
	}
	floyd(n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i != j and dist[i][j] < inf)
				add(i, n + j);
	std::cerr << "added" << std::endl;
	std::cout << n - hungrian(n << 1) << std::endl;
}
