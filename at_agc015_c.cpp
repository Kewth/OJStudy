#if 0
2019.12.15

森林的联通块数量等于点数减去边数，分别维护二维前缀和即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator bool () {
		int c = getchar();
		while(c != '0' and c != '1') c = getchar();
		return c == '1';
	}
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 4020;
bool a[maxn][maxn], b[maxn][maxn];
int sa[maxn][maxn], sb[maxn][maxn];

int main() {
	int n = read, m = read, q = read;

	for(int i = 2; i <= (n << 1); i += 2)
		for(int j = 2; j <= (m << 1); j += 2) {
			a[i][j] = read;
			b[i][j - 1] = (a[i][j] and a[i][j - 2]);
			b[i - 1][j] = (a[i][j] and a[i - 2][j]);
		}

	for(int i = 1; i <= (n << 1); i ++)
		for(int j = 1; j <= (m << 1); j ++)
			sa[i][j] = sa[i - 1][j] + sa[i][j - 1] + a[i][j] - sa[i - 1][j - 1];

	for(int i = 1; i <= (n << 1); i ++)
		for(int j = 1; j <= (m << 1); j ++)
			sb[i][j] = sb[i - 1][j] + sb[i][j - 1] + b[i][j] - sb[i - 1][j - 1];

	while(q --) {
		int x1 = read, y1 = read, x2 = read, y2 = read;
		x1 <<= 1;
		y1 <<= 1;
		x2 <<= 1;
		y2 <<= 1;
		printf("%d\n", sa[x2][y2] - sa[x2][y1 - 1] - sa[x1 - 1][y2] + sa[x1 - 1][y1 - 1] -
				(sb[x2][y2] - sb[x2][y1 - 1] - sb[x1 - 1][y2] + sb[x1 - 1][y1 - 1]));
	}
}
