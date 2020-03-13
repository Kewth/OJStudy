#if 0
2020.03.11

点亮技能树：DP 套 DP 。
这种 DP 套 DP 计数有共同点：假设计数的对象为 T 。
内层 DP 就是钦定 T = x 情况下判断对答案的贡献方式（这里贡献方式就是 LIS ）。
外层 DP 就是统计有多少 T 满足内层 DP 是什么什么样。
这里内层 DP 设 f[i][j] 表示 t 的前 i 位和 s 的前 j 位的 lis 长度。
外层 DP 设 F[i][S] 表示将 f 的第二维和值压在集合 S 中，有多少 t 满足条件。
由于 f[i][j] - f[i][j - 1] = 0/1 ，这里压这个差分数组即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cstring>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 16, maxm = 1005, mod = 1000000007;
char s[maxn];
ll f[2][1 << maxn];
int trans[1 << maxn][4];
int g[maxn], h[maxn];
ll ans[maxn];

int main() {
	char t[5] = "ATCG";

	int T = read;
	while(T --) {
		scanf("%s", s);
		int n = int(strlen(s)), m = read;

		for(int S = 0; S < (1 << n); S ++) {
			for(int i = 0; i < n; i ++)
				g[i + 1] = S >> i & 1;
			for(int i = 1; i <= n; i ++)
				g[i] += g[i - 1];

			for(int x = 0; x < 4; x ++) {
				for(int i = 1; i <= n; i ++)
					if(s[i - 1] == t[x])
						h[i] = g[i - 1] + 1;
					else
						h[i] = std::max(h[i - 1], g[i]);

				for(int i = n; i; i --)
					h[i] -= h[i - 1];
				trans[S][x] = 0;
				for(int i = 0; i < n; i ++)
					trans[S][x] |= h[i + 1] << i;
			}
		}

		for(int S = 1; S < (1 << n); S ++)
			f[0][S] = 0;
		f[0][0] = 1;

		for(int i = 1; i <= m; i ++) {
			int o = i & 1;
			for(int S = 0; S < (1 << n); S ++)
				f[o][S] = 0;
			for(int S = 0; S < (1 << n); S ++)
				for(int x = 0; x < 4; x ++)
					f[o][trans[S][x]] += f[!o][S];
			for(int S = 0; S < (1 << n); S ++)
				f[o][S] %= mod;
		}

		for(int i = 0; i <= n; i ++)
			ans[i] = 0;
		for(int S = 0; S < (1 << n); S ++)
			ans[__builtin_popcount(S)] += f[m & 1][S];

		for(int i = 0; i <= n; i ++)
			printf("%lld\n", ans[i] %= mod);
	}
}
