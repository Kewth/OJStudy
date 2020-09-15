/*
 * Author: Kewth

 * Date:
  2020.09.14

 * Solution:

 * Digression:

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 505, inf = 1000000000;
int dis[maxn][maxn];
ll f[maxn][maxn];
std::queue<par> q;
struct shit { int x, y; ll d; };
bool operator < (shit a, shit b) { return a.d > b.d; }
std::priority_queue<shit> sq;
// std::queue<shit> sq;

inline void update (int x, int y, int d) {
	if (dis[x][y] == inf)
		dis[x][y] = d, q.push(par(x, y));
}

inline void supdate (int x, int y, ll d) {
	if (d < f[x][y])
		f[x][y] = d, sq.push({x, y, d});
}

int main () {
	int n = read, m = read, a = read, b = read, c = read, N = read;
	++ n, ++ m;

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++)
			dis[i][j] = inf, f[i][j] = 1000000000000000000;

	int Sx = 0, Sy = 0, Tx = 0, Ty = 0;
	for (int i = 1; i <= N; i ++) {
		int x = read, y = read;
		++ x, ++ y;
		dis[x][y] = 0;
		q.push(par(x, y));
		if (i == 1) Sx = x, Sy = y;
		if (i == N) Tx = x, Ty = y;
		// debug("%d %d\n", x, y);
	}

	while (!q.empty()) {
		int x = q.front().first, y = q.front().second; q.pop();
		int d = dis[x][y] + 1;
		update(x - 1, y, d);
		update(x + 1, y, d);
		update(x, y - 1, d);
		update(x, y + 1, d);
	}

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m; j ++) {
			sq.push({i, j, f[i][j] =
					ll(std::abs(i - Sx) + std::abs(j - Sy)) * c});
		}

	while (!sq.empty()) {
		int x = sq.top().x, y = sq.top().y;
		ll d = sq.top().d;
		// int x = sq.front().x, y = sq.front().y;
		// ll d = sq.front().d;
		sq.pop();
		if (d > f[x][y]) continue;
		// debug("%d %d %lld\n", x, y, d);
		for (int i = 1; i <= n; i ++)
			supdate(i, y, d + 1ll * std::abs(i - x) * a + b + 1ll * dis[i][y] * c);
		supdate(x - 1, y, d + c);
		supdate(x + 1, y, d + c);
		for (int j = 1; j <= m; j ++)
			supdate(x, j, d + 1ll * std::abs(j - y) * a + b + 1ll * dis[x][j] * c);
		supdate(x, y - 1, d + c);
		supdate(x, y + 1, d + c);
	}

	printf("%lld\n", f[Tx][Ty]);
}
