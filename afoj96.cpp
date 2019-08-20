#if 0
2019.08.20

按高度从小到大考虑，每次把小的加水加到和旁边的齐平，对于齐平的若干相连的点可以合并一起考虑。
具体地，用并查集维护高度相同的连通块，每个连通块维护包围这个连通块的连通块，
每次选可以加水的最低的连通块 x，在包围它的连通块中选中最低的连通块 y ，
如果 y 比 x 低，说明 y 已经不能加水，那 x 也一定无法加水了，
否则，把 x 加水加到与 y 齐平，然后与 y 合并，包围集合可以启发式合并。
#endif
#include <cstdio>
#include <queue>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef std::pair<int, int> Par;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 305;
int high[maxn][maxn];
int fa[maxn * maxn];
std::priority_queue<Par> around[maxn * maxn];
bool die[maxn * maxn];

int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			high[i][j] = input();

	std::priority_queue<Par> q;

	for(int i = 0; i <= n + 1; i ++)
		for(int j = 0; j <= m + 1; j ++) {
			int k = i * (m + 2) + j;

			if(i < 1 or i > n or j < 1 or j > m)
				die[k] = true;

			if(j >= 1) around[k].push(Par(- high[i][j - 1], i * (m + 2) + j - 1));
			if(j <= m) around[k].push(Par(- high[i][j + 1], i * (m + 2) + j + 1));
			if(i >= 1) around[k].push(Par(- high[i - 1][j], (i - 1) * (m + 2) + j));
			if(i <= n) around[k].push(Par(- high[i + 1][j], (i + 1) * (m + 2) + j));

			while(not around[k].empty() and - around[k].top().first < high[i][j])
				around[k].pop();

			q.push(Par(- high[i][j], k));
		}

	for(int i = 0; i < (n + 2) * (m + 2); i ++)
		fa[i] = i;

	while(not q.empty()) {
		int x = q.top().second;
		q.pop();

		debug("%d %d\n", x / (m + 2), x % (m + 2));

		/* while(not around[x].empty()) */
		/* 	if(find(around[x].top().second) == x) */
		/* 		around[x].pop(); */
		/* 	else */
		/* 		break; */

		while(not around[x].empty() and find(around[x].top().second) == x)
			around[x].pop();

		if(die[x])
			while(not around[x].empty()) {
				int y = around[x].top().second;
				die[y] = true;
				around[x].pop();
			}

		if(not around[x].empty()) {
			int y = around[x].top().second;
			around[x].pop();

			debug("to %d %d\n", y / (m + 2), y % (m + 2));

			if(around[x].size() > around[y].size())
				std::swap(around[x], around[y]);

			assert(find(x) == x);

			fa[x] = y;
			while(not around[x].empty()) {
				around[y].push(around[x].top());
				around[x].pop();
			}
		}

	}

	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			int y = find(i * (m + 2) + j);
			printf("%d ", high[y / (m + 2)][y % (m + 2)] - high[i][j]);
		}
		puts("");
	}
}
