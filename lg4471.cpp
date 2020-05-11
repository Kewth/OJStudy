#if 0
2020.05.10

  相邻两个串可以接起来要么长度相等且仅第一个字符不同，要么长度相差一且一个是另一个的
后缀。将反串建 Trie 树 DP 即可。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 3000005, maxk = 26;
int ch[maxn][maxk], cp = 1;
bool word[maxn];
int f[maxn];
char s[maxn];

int ans = 1;
void dfs (int u) {
	int tot = 0, max = 0, semax = 0;
	for (int k = 0, v; k < maxk; k ++)
		if ((v = ch[u][k])) {
			dfs(v);
			if (word[v]) {
				++ tot;
				if (f[v] > max) {
					semax = max;
					max = f[v];
				} else if (f[v] > semax)
					semax = f[v];
			}
		}
	f[u] = tot + max;
	ans = std::max(ans, tot + max + semax + word[u]);
	/* debug("%d : %d %d %d\n", u, tot, max, semax); */
}

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) {
		scanf("%s", s + 1);
		int m = int(strlen(s + 1));
		int now = 1;
		for (int j = m; j; j --) {
			int &to = ch[now][s[j] - 'a'];
			if (!to) to = ++ cp;
			now = to;
		}
		word[now] = 1;
	}
	dfs(1);
	printf("%d\n", ans);
	/* debug("%lf\n", (sizeof ch) / 1024. / 1024.); */
}
