#if 0
2019.10.25
#endif
#include <cstdio>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 303;
char s[maxn][maxn];
int a[maxn][maxn];
bool vis[maxn][maxn];

const int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
bool find(int x, int y) {
	if(vis[x][y] or a[x][y] != 1) return 0;
	vis[x][y] = 1;
	for(int i = 0; i < 4; i ++)
		find(x + dx[i], y + dy[i]);
	return 1;
}

int main() {
	int n = input(), m = input();
	for(int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++)
			a[i][j] = s[i][j] - '0';
	int q = input();
	while(q --) {
		int x1 = input(), y1 = input(), x2 = input(), y2 = input();
		for(int i = x1; i <= x2; i ++)
			for(int j = y1; j <= y2; j ++)
				a[i][j] = 1;
		/* for(int i = 1; i <= n; i ++) { */
		/* 	for(int j = 1; j <= m; j ++) */
		/* 		debug("%d", a[i][j]); */
		/* 	debug("\n"); */
		/* } */
		memset(vis, 0, sizeof vis);
		int ans = 0;
		for(int i = 1; i <= n; i ++)
			for(int j = 1; j <= m; j ++)
				ans += find(i, j);
		printf("%d\n", ans);
	}
}
