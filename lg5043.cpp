/*
 * Author: Kewth

 * Date:
  2020.08.10

 * Solution:
  原来正经数哈希是 f[u] = 1 + sum(f[v] * p[size[v]]) 。

 * Digression:
  今天考试自己 yy 的树哈希被卡了。。。学个正经树哈希。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆■▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned long long hash;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 55;
const int N = 233;
bool nop[N + 1];
int pri[maxn], pp;
std::vector<int> G[maxn];
int size[maxn];
hash f[maxn];

hash dfs (int u, int fa) {
	hash res = 1;
	size[u] = 1;
	for (int v : G[u])
		if (v != fa) {
			hash tmp = dfs(v, u);
			size[u] += size[v];
			res += tmp * hash(pri[size[v]]);
		}
	return res;
}

int main () {
	for (int i = 2; i <= N; i ++)
		if (!nop[i]) {
			if (i <= N / i)
				for (int j = i * i; j <= N; j += i)
					nop[j] = 1;
			pri[++ pp] = i;
		}

	int m = read;
	for (int i = 1; i <= m; i ++) {
		int n = read;
		for (int u = 1; u <= n; u ++) G[u].clear();
		for (int u = 1; u <= n; u ++) {
			int v = read;
			if (v) {
				G[u].push_back(v);
				G[v].push_back(u);
			}
		}
		for (int u = 1; u <= n; u ++)
			f[i] = std::max(f[i], dfs(u, 0));
		for (int j = 1; j <= i; j ++)
			if (f[i] == f[j]) {
				printf("%d\n", j);
				goto get;
			}
get:;
	}
}
