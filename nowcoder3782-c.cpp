#if 0
2020.01.19

感觉我是傻逼，只知道把最长反链转换成最小链覆盖，不知道把最小链覆盖转换成最长反链。

先考虑求出不删点的情况的答案 ans 。
将满足 i < j 且 a[i] > a[j] 的点对 (i, j) 连边 i -> j ，
那么 ans 就是这张图的最小链覆盖，即最长反链，即最长不降子序列。

那么一个点的答案是 ans - 1 当且仅当它出现在所有最长不降子序列中，否则答案是 ans 。
设 f[i], g[i] 分别表示以 i 为开头结尾时的最长不降子序列长，
如果 f[i] + g[i] - 1 = ans ，说明 i 出现在至少一个最长不降子序列中，称这样的 i 为 key 。
如果所有 key 中 f[i] 只出现了一次，那么这个 i 就会出现在所有最长不降子序列中。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005;
int tmp[maxn], a[maxn];
int bit[maxn];
int f[maxn], g[maxn];
int tot[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		tmp[i] = a[i] = read;

	std::sort(tmp + 1, tmp + n + 1);
	for(int i = 1; i <= n; i ++)
		a[i] = int(std::lower_bound(tmp + 1, tmp + n + 1, a[i]) - tmp);

	int ans = 0;
	for(int i = 1; i <= n; i ++) {
		int &now = f[i];
		for(int k = a[i]; k; k -= k & -k)
			now = std::max(now, bit[k]);
		ans = std::max(ans, ++ now);
		for(int k = a[i]; k <= n; k += k & -k)
			bit[k] = std::max(bit[k], now);
	}

	for(int i = 1; i <= n; i ++)
		bit[i] = 0;

	for(int i = n; i; i --) {
		int &now = g[i];
		for(int k = n + 1 - a[i]; k; k -= k & -k)
			now = std::max(now, bit[k]);
		++ now;
		for(int k = n + 1 - a[i]; k <= n; k += k & -k)
			bit[k] = std::max(bit[k], now);
	}

	for(int i = 1; i <= n; i ++)
		if(f[i] + g[i] - 1 == ans)
			++ tot[f[i]];

	for(int i = 1; i <= n; i ++)
		if(f[i] + g[i] - 1 == ans and tot[f[i]] == 1)
			printf("%d ", ans - 1);
		else
			printf("%d ", ans);
	puts("");
}
