#if 0
2019.12.07

对于一个 2x2 的矩形，可以全黑当且仅当有偶数个黑块。
那么长宽不小于 2 的矩形可以全黑的一个必要条件是所有的 2x2 子矩阵有偶数个黑点。
事实上这也是充分条件，那么把每个 2x2 子矩阵看作一个新的点，该点为黑当且仅当原来有偶数个黑点。
新矩阵的每个全为黑点的 axb 的子矩阵就对应源矩阵一个 (a+1)x(b+1) 的可以全黑的子矩阵。
在新矩阵上枚举全黑子矩阵的上边界的最低点的下边界即可求出最大全黑子矩阵（悬线法）。
另外特判长或宽为 1 的子矩阵即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 2020;
char s[maxn][maxn];
bool ok[maxn][maxn];
int up[maxn];
int lmin[maxn], rmin[maxn];

int main() {
	int n = read, m = read;

	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);

	for(int i = 1; i < n; i ++)
		for(int j = 1; j < m; j ++) {
			int x = (s[i][j] == '#') + (s[i][j + 1] == '#') +
				(s[i + 1][j] == '#') + (s[i + 1][j + 1] == '#');
			ok[i][j] = !(x & 1);
		}

	int ans = std::max(n, m);

/* 	for(int i = 1; i < n; i ++) { */
/* 		for(int j = 1; j < m; j ++) */
/* 			debug("%c", ".#"[ok[i][j]]); */
/* 		debug("\n"); */
/* 	} */

	for(int i = 1; i < n; i ++) {
		for(int j = 1; j < m; j ++)
			if(ok[i][j]) ++ up[j];
			else up[j] = 0;

		for(int j = 1; j < m; j ++) {
			int &l = (lmin[j] = j - 1);
			while(l and up[l] >= up[j])
				l = lmin[l];
		}

		for(int j = m - 1; j; j --) {
			int &r = (rmin[j] = j + 1);
			while(r < m and up[r] >= up[j])
				r = rmin[r];
		}

		for(int j = 1; j < m; j ++)
			ans = std::max(ans, (up[j] + 1) * (rmin[j] - lmin[j]));
	}

	printf("%d\n", ans);
}
