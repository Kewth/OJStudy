#if 0
2019.08.20

一般性的最小路径覆盖用 floyd 传递闭包处理出点之间的到达关系后建立二分图，
最初有 n 条路径，每条路径对应一个点，这个状态对应二分图无匹配。
二分图每次匹配 (x1, y2) 代表着把 x 所在路径连向 y 所在路径，匹配 +1 ，路径覆盖 -1 。
这题要求路径之间没有公共点，去掉传递闭包那部分即可。
#endif
#include <cstdio>
#include <cstring>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 155, maxd = 310, maxm = 100000;
int head[maxd], nxt[maxm << 1], to[maxm << 1], cap[maxm << 1], hp = 1;
int tmp[maxd];
int level[maxd];
bool link[maxn][maxn];
int pfrom[maxn], pto[maxn];

inline void add(int u, int v) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = 1;

	nxt[++ hp] = head[v];
	head[v] = hp;
	to[hp] = u;
	cap[hp] = 0;
}

bool bfs(int s, int t) {
	memset(level, -1, sizeof level);
	level[s] = 0;

	std::queue<int> q;
	q.push(s);

	while(not q.empty()) {
		int u = q.front();
		q.pop();

		for(int i = head[u]; i; i = nxt[i])
			if(cap[i] and level[to[i]] == -1) {
				level[to[i]] = level[u] + 1;
				q.push(to[i]);
			}
	}

	return ~level[t];
}

int dfs(int u, int t, int f) {
	if(u == t)
		return f;

	for(int &i = head[u]; i; i = nxt[i])
		if(cap[i] and level[to[i]] == level[u] + 1) {
			int ff = dfs(to[i], t, std::min(f, cap[i]));
			if(ff) {
				cap[i] -= ff;
				cap[i ^ 1] += ff;
				return ff;
			}
		}

	return 0;
}

int dinic(int s, int t) {
	memcpy(tmp, head, sizeof tmp);

	int res = 0;

	while(bfs(s, t)) {
		int f;
		do {
			f = dfs(s, t, 1000000000);
			res += f;
		} while(f);

		memcpy(head, tmp, sizeof tmp);
	}

	return res;
}

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= m; i ++) {
		int u = input(), v = input();
		link[u][v] = true;
	}

	/* for(int k = 1; k <= n; k ++) */
	/* 	for(int i = 1; i <= n; i ++) */
	/* 		for(int j = 1; j <= n; j ++) */
	/* 			if(link[i][k] and link[k][j]) */
	/* 				link[i][j] = true; */

	for(int i = 1; i <= n; i ++) {
		add(n * 2 + 1, i);
		add(n + i, n * 2 + 2);
	}

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= n; j ++)
			if(link[i][j])
				add(i, n + j);

	dinic(n * 2 + 1, n * 2 + 2);

	for(int u = 1; u <= n; u ++)
		for(int i = head[u]; i; i = nxt[i])
			if(to[i] > n and to[i] <= n * 2 and cap[i] == 0) {
				pfrom[to[i] - n] = u;
				pto[u] = to[i] - n;
			}

	int tot = 0;
	for(int u = 1; u <= n; u ++)
		if(not pfrom[u]) {
			for(int v = u; v; v = pto[v])
				printf("%d ", v);
			puts("");
			tot ++;
		}
	printf("%d\n", tot);
}
