#if 0
2019.12.25

Ynoi 惊现水题！
记 f[u][x] 表示二元组 (u, x) 能覆盖的点，用 bitset 存，
预处理 f 就是跑 n 遍 bfs 最短路求出所有点对的距离然后前缀求并。
对于询问将若干 f[u][x] 并起来求 1 的个数即可。
#endif
#include <cstdio>
#include <vector>
#include <bitset>
#include <queue>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 1010;
std::vector<int> G[maxn];
int dis[maxn][maxn];
std::bitset<maxn> f[maxn][maxn];

void bfs(int s) {
	std::queue<int> q;
	q.push(s);
	int *di = dis[s];
	di[s] = 0;
	while(!q.empty()) {
		int u = q.front();
		q.pop();
		for(int v : G[u])
			if(di[v] == -1) {
				di[v] = di[u] + 1;
				q.push(v);
			}
	}
}

int main() {
	int n = read, m = read, q = read;

	for(int i = 1; i <= m; i ++) {
		int u = read, v = read;
		G[u].push_back(v);
		G[v].push_back(u);
	}

	memset(dis, -1, sizeof dis);

	for(int i = 1; i <= n; i ++)
		bfs(i);

	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= n; j ++)
			f[i][dis[i][j]][si(j)] = 1;
		for(int j = 1; j <= n; j ++)
			f[i][j] |= f[i][j - 1];
	}

	while(q --) {
		int a = read;
		std::bitset<maxn> S;
		while(a --) {
			int u = read, x = read;
			S |= f[u][x];
		}
		printf("%lu\n", S.count());
	}
}
