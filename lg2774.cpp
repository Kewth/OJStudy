#if 0
2019.08.20

题目可抽象为：
有若干元素，每个元素选了可以产生贡献，
有若干限定条件，每个条件限定某两个点不能同时选。

先拿到所有贡献，那么元素不选则产生代价。
注意到限定条件的两个点 (x, y), (a, b) 有 x + y 与 a + b 奇偶性不同，
可转换到最小割模型。
#endif
#include <cstdio>
#include <cstring>
#include <queue>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 105, maxd = 30000, maxm = 200000;
int head[maxd], nxt[maxm << 1], to[maxm << 1], cap[maxm << 1], hp = 1;
int tmp[maxd];
int level[maxd];

inline void add(int u, int v, int w) {
	nxt[++ hp] = head[u];
	head[u] = hp;
	to[hp] = v;
	cap[hp] = w;

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

	auto lid = [&](int x, int y) {
		return x * m + y;
	};

	auto rid = [&](int x, int y) {
		return n * m + x * m + y;
	};

	int s = n * m * 2, t = n * m * 2 + 1;
	int fuck = 1000000;
	int ans = 0;

	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++) {
			int now = input();
			ans += now;

			add(lid(i, j), rid(i, j), INT_MAX);

			if((i + j) & 1) {
				if(j)
					add(lid(i, j), rid(i, j - 1), INT_MAX);
				if(j + 1 < m)
					add(lid(i, j), rid(i, j + 1), INT_MAX);
				if(i)
					add(lid(i, j), rid(i - 1, j), INT_MAX);
				if(i + 1 < n)
					add(lid(i, j), rid(i + 1, j), INT_MAX);

				add(s, lid(i, j), fuck + now);
				add(rid(i, j), t, fuck);
			}

			else {
				add(s, lid(i, j), fuck);
				add(rid(i, j), t, fuck + now);
			}
		}

	printf("%d\n", ans - dinic(s, t) + n * m * fuck);

	/* for(int i = head[s]; i; i = nxt[i]) */
	/* 	if((to[i] / m + to[i] % m) & 1 and cap[i]) */
	/* 		debug("%d %d\n", to[i] / m, to[i] % m); */
}
