#if 0
2020.03.25

最后每一行的数的和是确定的，如果一行确定了删掉某一个数 x ，那么就可以直接确定放入该行的数。
对于这个关系连边，问题就是要找到若干环，满足这些环所在的行的集合是全集的一个划分。
DP f[S] 表示考虑行的集合 S 是否存在合法划分，转移枚举子集，
然后记录转移方向即可得出最终的划分，进而输出方案。
#endif
#include <cstdio>
#include <algorithm>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 16, maxm = 5050;
ll a[maxn][maxm];
int m[maxn];
ll s[maxn];
std::map<ll, par> map;
par to[maxn][maxm];
int deg[maxn][maxm];
par stack[maxn * maxm];
int sp;
bool f[1 << maxn];
int g[1 << maxn];
par h[1 << maxn];
int use[maxn], put[maxn];

void getans (int S) {
	if (g[S] == -1) {
		int x = h[S].first, y = h[S].second;
		do {
			par p = to[x][y];
			use[x] = y;
			put[p.first] = x;
			x = p.first;
			y = p.second;
		} while (x != h[S].first or y != h[S].second);
		return;
	}
	int A = g[S], B = S ^ A;
	getans(A);
	getans(B);
}

int main () {
	int n = read;
	ll sum = 0;
	for (int i = 1; i <= n; i ++) {
		read(m[i]);
		for (int j = 1; j <= m[i]; j ++) {
			s[i] += a[i][j] = read;
			map[a[i][j]] = par(i, j);
		}
		sum += s[i];
	}

	if (sum % n) return puts("No"), 0;
	sum /= n;
	for (int i = 1; i <= n; i ++)
		s[i] -= sum;

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m[i]; j ++) {
			ll x = a[i][j] - s[i];
			if (map.count(x)) {
				par p = map[x];
				to[i][j] = p;
				/* debug("%d %d -> %d %d\n", i, j, p.first, p.second); */
				++ deg[p.first][p.second];
			}
		}

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m[i]; j ++)
			if (!deg[i][j])
				stack[++ sp] = par(i, j);

	while (sp) {
		int i = stack[sp].first, j = stack[sp].second;
		-- sp;
		if (to[i][j] != par(0, 0) and -- deg[to[i][j].first][to[i][j].second] == 0)
			stack[++ sp] = to[i][j];
	}

	for (int i = 1; i <= n; i ++)
		for (int j = 1; j <= m[i]; j ++)
			if (deg[i][j]) {
				int x = i, y = j, S = 0, shit = 0;
				/* debug("circle\n"); */
				do {
					/* debug("%d %d\n", x, y); */
					deg[x][y] = 0;
					shit |= S << 1 >> x & 1;
					S ^= 1 << x >> 1;
					par p = to[x][y];
					x = p.first;
					y = p.second;
				} while (x != i or y != j);
				if (!shit)
					f[S] = 1, g[S] = -1, h[S] = par(i, j);
			}

	for (int S = 0; S < (1 << n); S ++)
		for (int A = S; A >= 0 and !f[S]; A --) {
			A &= S;
			int B = S ^ A;
			if (f[A] and f[B])
				f[S] = 1, g[S] = A;
		}

	if (!f[(1 << n) - 1]) return puts("No"), 0;
	getans((1 << n) - 1);

	puts("Yes");
	for (int i = 1; i <= n; i ++)
		printf("%lld %d\n", a[i][use[i]], put[i]);

	for (int i = 1; i <= n; i ++) {
		s[i] -= a[i][use[i]];
		s[put[i]] += a[i][use[i]];
	}

	for (int i = 1; i <= n; i ++)
		if (s[i])
			return 1;
}
