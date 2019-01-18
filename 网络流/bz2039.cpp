// include files {{{1
#include <bits/stdc++.h>

// Global definition {{{1
const int maxn = 1050, maxm = 1050*1050*2;
const int inf = 1000000000;
int to[maxm], cap[maxm], nxt[maxm], p = 1;
int level[maxn], head[maxn], Head[maxn];

int use[maxn], know[maxn][maxn];

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
	/* std::cerr << level[t] << std::endl; */
	return res;
}

// dfs {{{1
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

// Max flow {{{1
int maxflow(int s, int t) {
	long long res = 0;
	while(bfs(s, t)) {
		memcpy(Head, head, sizeof(Head));
		int now = 0;
		do {
			now = dfs(s, t, inf);
			res += now;
		} while(now);
		/* /1* debug *1/ { */
		/* 	long long sum = 0; */
		/* 	for(int i=head[s];i;i=nxt[i]) */
		/* 		sum += cap[i]; */
		/* 	std::cerr << sum << std::endl; */
		/* } */
		/* std::cerr << "1 " << res << std::endl; */
		/* std::cerr << "2 " << now << std::endl; */
	}
	return res;
}

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
	ans -= maxflow(S, T);
	std::cout << ans << std::endl;
}

// {{{1
// }}}1
