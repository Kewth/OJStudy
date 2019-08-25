#if 0
2019.08.25

一个更加广泛的问题是：n 个点 m 条边是否有 k 个不重边的生成树。
香农游戏相当于 k = 2 的情况，可以直接爆搜，
依次考虑每条边被加在哪个集合，实际上复杂度是有保障的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 303;
int fa[maxn][maxn], deep[maxn][maxn];
int a[maxn], b[maxn];

inline int find(int p, int x) {
	while(fa[p][x] != x)
		x = fa[p][x];
	return x;
}

int get;
inline void merge(int p, int x, int y) {
	if(deep[p][x] > deep[p][y])
		std::swap(x, y);
	if(deep[p][x] == deep[p][y])
		deep[p][y] ++;
	fa[p][x] = y;
	get ++;
}

inline void undo(int p, int x, int y) {
	fa[p][x] = x;
	fa[p][y] = y;
	get --;
}

int n, m, k;
bool fuck(int d) {
	if(d + get < k * (n - 1))
		return false;
	if(d == 0)
		return true;
	/* debug("%d\n", d); */
	int x = a[d], y = b[d];
	bool found = false;
	for(int i = 1; i <= k; i ++) {
		int xx = find(i, x), yy = find(i, y);
		if(xx != yy) {
			found = true;
			merge(i, xx, yy);
			bool f = fuck(d - 1);
			undo(i, xx, yy);
			if(f)
				return true;
		}
	}
	return found ? false: fuck(d - 1);
}

int main() {
	int T = input();
	while(T --) {
		n = input(), m = input(), k = input();

		for(int i = 1; i <= m; i ++) {
			a[i] = input();
			b[i] = input();
		}

		if((n - 1) * k > m) {
			puts("Impossible");
			continue;
		}

		for(int i = 1; i <= k; i ++)
			for(int j = 1; j <= n; j ++) {
				fa[i][j] = j;
				deep[i][j] = 0;
			}

		get = 0;
		if(fuck(m))
			puts("Possible");
		else
			puts("Impossible");
	}
}
