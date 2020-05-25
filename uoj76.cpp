#if 0
2020.05.24

  一个朴素的状压 DP 是设 f[S] 表示生病的集合为 S 时的开枪时间。转移枚举每个生病的狗主
人 x ，再枚举其不能看到的点的生病情况。
  抽象这个 DP ，可以发现，如果建一个新图，i 向 j 连边当且仅当 i 不能看到 j ，那么对于
f[S] ，把 S 内的点染黑表示生病，一个合法的转移就是选择一个黑色点 x ，把 x 变白，再把
枚举 x 连接的点的所有连接情况，最大的使得整张图变白的转移次数就是 f[S] 的值。
  不难发现如果把一个白点变成黑点转移次数不减，那么上述的枚举连接情况是没必要的，在确
定 x 后，只需要把 x 连接的点全部染黑即可。
  这样一来把问题放在了新图上，就很好处理了。首先如果任意一个环上有一个黑点，转移就无
法在有限时间内结束，进一步的，如果存在一个黑点 x 可以到达任意一个环，转移就是无法结
束的。那么把这些无法结束的点删掉，剩下的图就变成了若干 DAG 。
  那么对于确定的 S ，其转移次数就是 S 能到达的点集的大小。对于每个点算贡献，也就是算
有多少集合 S 存在能到达它的点即可。只需要 O(n^3/w) 预处理每个点的能被到达的点集即可。
        ▁▃▄▄▄▃▃▃▃▄▶
      ▗▇▀▔    ▔▔▔▔
     ▄▛   ▃▅━━■▄▂
    ▟▊   ▐▘     ▀▙
   ▟▜▌   ▐▖   ▋  ▐▍
  ▟▘ ▜   ▝▀▇▆●▘  ▐▌
▗▟▘   ▜▃       ▁▅▛
▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔   CopyRight :)
      ▔▔▔▔▔▔
#endif
#include <cstdio>
#include <algorithm>
#include <bitset>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 3005, mod = 998244353;
char s[maxn][maxn];
int deg[maxn];
int topsort[maxn], tp;
std::bitset<maxn> bs[maxn];
ll po[maxn];

inline bool link (int x, int y) { return x != y and s[y][x] == '0'; }

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++)
		scanf("%s", s[i] + 1);

	for (int i = 1; i <= n; i ++) {
		for (int j = 1; j <= n; j ++)
			if (link(j, i))
				++ deg[i];
		if (!deg[i]) topsort[++ tp] = i;
	}

	for (int i = 1; i <= tp; i ++) {
		int u = topsort[i];
		for (int v = 1; v <= n; v ++)
			if (link(u, v) and -- deg[v] == 0)
				topsort[++ tp] = v;
	}

	po[0] = 1;
	for (int i = 1; i <= n; i ++)
		po[i] = po[i - 1] * 2 % mod;

	ll ans1 = 0, ans2 = 0;
	for (int i = tp; i; i --) {
		int u = topsort[i];
		bs[u].set(si(u));
		for (int v = 1; v <= n; v ++)
			if (link(u, v))
				bs[u] |= bs[v];
		int k = int(bs[u].count());
		(ans1 += (po[k] - 1) * po[tp - k]) %= mod;
		(ans2 += po[tp - k]) %= mod;
	}

	printf("%lld %lld\n", ans1, ans2);
}
