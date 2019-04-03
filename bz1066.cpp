// include files {{{1
#include <bits/stdc++.h>

// Global definition {{{1
const int maxn = 40;
const int inf = 1000000000;
int head[maxn*maxn], to[maxn*maxn*maxn], cap[maxn*maxn*maxn], nxt[maxn*maxn*maxn], p = 1;
int level[maxn*maxn];
char high[maxn][maxn], map[maxn][maxn];
int id[maxn][maxn], ip = 0;

// add edge into graph {{{1
void add(int x, int y, int c) {
	nxt[++p] = head[x];
	to[p] = y;
	cap[p] = c;
	head[x] = p;
	nxt[++p] = head[y];
	to[p] = x;
	cap[p] = 0;
	head[y] = p;
	/* std::cerr << x << " link to " << y << std::endl; */
}

// bfs {{{1
bool bfs(int s, int t) {
	bool res = false;
	std::queue<int> q;
	q.push(s);
	memset(level, 0, sizeof(level));
	level[s] = 1;
	while(not q.empty()) {
		int u = q.front();
		q.pop();
		if(u == t) res = true;
		for(int i=head[u];i;i=nxt[i]) {
			int v = to[i];
			if(not level[v] and cap[i]) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return res;
}

// dfs {{{1
int dfs(int u, int t, int c) {
	if(u == t)
		return c;
	for(int i=head[u];i;i=nxt[i]) {
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

// Max flow {{{1
int maxflow(int s, int t) {
	int res = 0;
	bfs(s, t);
	while(true) {
		/* std::cerr << res << std::endl; */
		int now = dfs(s, t, inf);
		res += now;
		if(not now)
			if(not bfs(s, t))
				return res;
	}
}

// Main function {{{1
int main(const int, const char **) {
	std::ios::sync_with_stdio(false);
	int n, m, k, tot = 0;
	std::cin >> n >> m >> k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			std::cin >> high[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			std::cin >> map[i][j];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(high[i][j] != '0') {
				id[i][j] = ++ ip;
				add(id[i][j], ++ip, high[i][j] - '0');
				if(map[i][j] == 'L') {
					add(0, id[i][j], 1);
					tot ++;
				}
				if(i <= k or j <= k or i > n - k or j > m - k)
					add(id[i][j]+1, n*m<<1, inf);
			}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int ii=1;ii<=n;ii++)
				for(int jj=1;jj<=m;jj++)
					if(id[ii][jj] and (i != ii or j != jj)
							and (i-ii)*(i-ii) + (j-jj)*(j-jj) <= k*k) {
						add(id[i][j]+1, id[ii][jj], inf);
					}
	std::cout << tot - maxflow(0, n*m<<1) << std::endl;
}

// {{{1
// }}}1
