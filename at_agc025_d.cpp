#pragma GCC optimize(3)
#if 0
2020.03.15

假设只有一个限制，将距离为 d 的点连边，一定会形成二分图。
二分图染色后对每个连通块取较大的一部分即可。
在加一个限制也是一样，对于前一个限制处理出来的点再进行一次二分图染色，
同样取较大的一部分，就可以得到足够多的点。
需要预处理所有模长为 d 的整向量，作为连边的依据。
复杂度 O(n^2 k) , k 为模长为 d 的整向量数。
#endif
#include <cstdio>
#include <cmath>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 605;
int c[2][maxn][maxn];
int tot[2][maxn * maxn];
bool mark[2][maxn * maxn];
std::vector<par> v;
int n;

void dfs(int x, int y, int co, int o) {
	if(x < 0 or x >= n * 2 or y < 0 or y >= n * 2 or c[o][x][y] or
			(o == 1 and !mark[0][c[0][x][y]])) return;
	c[o][x][y] = co;
	++ tot[o][co];
	for(par p : v) {
		dfs(x - p.first, y - p.second, co ^ 1, o);
		dfs(x - p.first, y + p.second, co ^ 1, o);
		dfs(x + p.first, y - p.second, co ^ 1, o);
		dfs(x + p.first, y + p.second, co ^ 1, o);
	}
}

int main() {
	n = read;

	for(int o = 0; o < 2; o ++) {
		int dis = read;
		v.clear();
		for(int x = 0; x < n * 2 and x * x <= dis; x ++) {
			int y = int(sqrt(dis - x * x));
			if(x * x + y * y == dis)
				v.push_back(par(x, y));
		}

		int co = 0;
		for(int x = 0; x < n * 2; x ++)
			for(int y = 0; y < n * 2; y ++)
				if(!c[o][x][y]) {
					++ co;
					dfs(x, y, co << 1, o);
				}

		for(int i = 1; i <= co; i ++)
			if(tot[o][i << 1] > tot[o][i << 1 | 1])
				mark[o][i << 1] = 1;
			else
				mark[o][i << 1 | 1] = 1;
	}

	int need = n * n;
	for(int x = 0; x < n * 2; x ++)
		for(int y = 0; y < n * 2; y ++)
			if(mark[1][c[1][x][y]] and need) {
				printf("%d %d\n", x, y);
				-- need;
			}

	if(need) return 1;
}
