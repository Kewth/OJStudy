#if 0
2020.01.21

人间之屑。

特判掉一条链的情况，
然后找到一个度数为 2 的点，作为网格图的端点，从它开始 BFS ，
BFS 每一层是网格图的一个斜线，逐个确定每个坐标的点即可，
中途出现奇怪情况就判非网格。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	/* inline operator ll () { ll x; return scanf("%lld", &x), x; } */
	/* template<class T> inline void operator () (T &x) { x = *this; } */
	/* template<class T, class ...A> inline void operator () (T &x, A &...a) */
	/* { x = *this; this -> operator ()(a...); } */
} read;

const int maxn = 105;
std::vector<int> G[maxn];
int map[maxn][maxn];
bool inmap[maxn];
size_t get[maxn];

void clear() {
	memset(map, 0, sizeof map);
	memset(inmap, 0, sizeof inmap);
	memset(get, 0, sizeof get);
}

bool check(int n, int m) {
	clear();

	if(m == n - 1) {
		for(int i = 1; i <= n; i ++)
			if(G[i].size() > 2)
				return 0;
		return 1;
	}

	int s = 0;
	for(int i = 1; i <= n; i ++)
		if(G[i].size() == 2)
			s = i;
	if(!s) return 0;

	for(int i = 1; i <= n; i ++)
		if(G[i].size() == 1 or G[i].size() > 4)
			return 0;

	int tot = 1;
	map[1][1] = s;
	inmap[s] = 1;

	int sum = 3;
	while(tot < n) {
		int baktot = tot;

		for(int x = 2; x <= sum - 2; x ++) {
			int y = sum - x;
			int u1 = map[x][y - 1], u2 = map[x - 1][y];
			if(!u1 or !u2) continue;

			for(int v1 : G[u1])
				for(int v2 : G[u2])
					if(v1 == v2 and !inmap[v1]) {
						map[x][y] = v1;
						inmap[v1] = 1;
						++ get[u1];
						++ get[u2];
						++ tot;
						get[v1] += 2;
						goto get;
					}
			return 0;
get:;
		}

		if(map[1][sum - 2]) {
			int u = map[1][sum - 2];
			for(int v : G[u])
				if(!inmap[v]) {
					map[1][sum - 1] = v;
					inmap[v] = 1;
					++ get[u];
					++ get[v];
					++ tot;
					break;
				}
		}

		if(map[sum - 2][1]) {
			int u = map[sum - 2][1];
			for(int v : G[u])
				if(!inmap[v]) {
					map[sum - 1][1] = v;
					inmap[v] = 1;
					++ get[u];
					++ get[v];
					++ tot;
					break;
				}
		}

		if(tot == baktot) {
			-- sum;
			break;
		}
		++ sum;
	}

	if(tot < n) return 0;

	for(int i = 1; i <= n; i ++)
		if(get[i] != G[i].size())
			return 0;

	for(int x = 1; x < sum; x ++)
		if(map[x][sum - x]) {
			int t = map[x][sum - x];
			if(G[t].size() != 2) return 0;
			if(x * (sum - x) != n) return 0;
		}

/* 	for(int x = 1; x <= 10; x ++) { */
/* 		for(int y = 1; y <= 10; y ++) */
/* 			debug(" %d", map[x][y]); */
/* 		debug("\n"); */
/* 	} */
/* 	debug("\n"); */

	return 1;
}

int main() {
	int T = read;
	while(T --) {
		int n = read, m = read;
		for(int i = 1; i <= n; i ++)
			G[i].clear();
		for(int i = 1; i <= m; i ++) {
			int u = read, v = read;
			G[u].push_back(v);
			G[v].push_back(u);
		}
		if(check(n, m))
			puts("Shi");
		else
			puts("Fou");
	}
}
