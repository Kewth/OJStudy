#if 0
2019.10.25

由于 0 变 1 的发生次数最多是 O(nm) 的，考虑在每次矩阵修改时只对其中的 0 进行修改。
枚举行，对于每一行用并查集维护每一个点的下一个 0 是哪里即可。
然后每次 0 变 1 的时候维护答案，同样用并查集维护每个点所属的联通块，
每次 0 变 1 可以看做产生新的联通块，答案 + 1 ，
并查集每次合并意味着两个联通块相接，答案 -1 。
#endif
#include <cstdio>
#include <cstring>
/* #include <set> */
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 1010;
char s[maxn][maxn];
/* std::set<int> set[maxn]; */

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};

int nxt[maxn][maxn];
int fa[maxn * maxn];
/* int a[maxn * maxn]; */
int find(int x) {
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
int NXT(int x, int y) {
	if(nxt[x][y] == y) return y;
	return nxt[x][y] = NXT(x, nxt[x][y]);
}

int ans = 0;
void update(int x, int y) {
	nxt[x][y] = y + 1;
	fa[x * maxn + y] = x * maxn + y;
	ans ++;
	for(int i = 0; i < 4; i ++) {
		int X = x + dx[i], Y = y + dy[i];
		if(fa[X * maxn + Y] and find(X * maxn + Y) != x * maxn + y) {
			/* debug("%d %d link %d %d\n", x, y, X, Y); */
			fa[find(X * maxn + Y)] = x * maxn + y;
			ans --;
		}
	}
	/* debug("update %d %d -> %d\n", x, y, ans); */
}

int tmp[maxn];
int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++)
			if(s[i][j] == '1')
				update(i, j);
			else {
				/* set[i].insert(j); */
				nxt[i][j] = j;
			}
		nxt[i][m + 1] = m + 1;
	}
	int q = input();
	while(q --) {
		int x1 = input(), y1 = input(), x2 = input(), y2 = input();
		for(int i = x1; i <= x2; i ++) {
			int ii = NXT(i, y1);
			while(ii <= y2) {
				/* debug("%d %d\n", i, ii); */
				update(i, ii);
				ii = NXT(i, ii);
			}
		}
		printf("%d\n", ans);
	}
}
