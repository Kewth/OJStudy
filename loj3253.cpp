#if 0
2020.05.13

  问题相当于求最小的子串满足存在一个 k 级 JOI 串的子序列。
  在字符串前面强行添加一个 k 级 JOI 串。然后处理出 pre[x][i] 表示前缀 i 倒数第 k 个 x 字符
的位置。为了计算 pre 还需要处理 nxt[x][i] 表示位置大于 i 的 x 字符的最小位置。然后枚举右端
点，跳 pre 找到最大的合法的左端点即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 400005;
char s[maxn];
int pre[3][maxn], nxt[3][maxn];

int main () {
	int n = read, m = read;
	scanf("%s", s + m * 3 + 1);
	for (int i = 1; i <= m; i ++) {
		s[i] = 'J';
		s[m + i] = 'O';
		s[m + m + i] = 'I';
	}
	for (int i = 1; i <= m * 3; i ++)
		if (i % m)
			nxt[i / m][i] = i + 1;
	n += m * 3;

	char t[] = "JOI";
	int las[3] = {m, m + m, m + m + m};
	pre[0][m * 3] = 1;
	pre[1][m * 3] = 1 + m;
	pre[2][m * 3] = 1 + m + m;

	int ans = 1000000000;
	for (int i = m * 3 + 1; i <= n; i ++) {
		for (int x = 0; x < 3; x ++)
			if (t[x] == s[i]) {
				nxt[x][las[x]] = i;
				las[x] = i;
				pre[x][i] = nxt[x][pre[x][i - 1]];
			} else
				pre[x][i] = pre[x][i - 1];
		/* debug("%d %d %d\n", pre[0][i], pre[1][i], pre[2][i]); */
		int j = i;
		j = pre[2][j];
		j = pre[1][j];
		j = pre[0][j];
		if (j > m * 3) ans = std::min(ans, i - j + 1 - m * 3);
	}

	printf("%d\n", ans == 1000000000 ? -1 : ans);
}
