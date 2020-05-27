#if 0
2020.05.26

  奇妙，首先问题不难转换为异或卷积的模型，并且每个数组只有两个位置有值，FWT 后只有 1 - b
和 1 + b 两种取值，不妨设 f[i] 为第 i 个位置所有 FWT 后的数组在该位置上的乘积，那么只要
求出 f 就能得到答案（IFWT 后第 0 个位置的值）。
  设 g[i] 是把 f[i] 的构成中所有 1 + b / 1 - b 替换为 1 - b / 1 + b 的值，也就是说满足
f[i] * g[i] = mul(1 - b^2) 。类似于 FWT 那样枚举每个维度，在 f, g 之间相互转移，一开始
f[i], g[i] 的值只有 mul(1 + b[i]) 和 mul(1 - b[i]) ，每加入一个维度就在该维度上合并，每
个 f, g 的取值涉及到的位置就会翻倍。实现上也是和 FWT 完全一致的 3 个 for ，在里面转移即
可。
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
#include <cstdlib>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct Inputer {
	static char buffer[128 * 1024 * 1024], *p;
	inline operator int () { return int(strtol(p, &p, 10)); }
	inline operator ll () { return strtoll(p, &p, 10); }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
	Inputer() { fread(buffer, 1, sizeof buffer, stdin); }
} read;
char *Inputer::p = Inputer::buffer;
char Inputer::buffer[] = {};

const int maxn = 17, mod = 998244353;
ll f[1 << maxn], g[1 << maxn];

void F_WTF_T (int n) {
	for (int m = 1; m < n; m <<= 1) {
		for (int i = 0; i < n; i += m << 1)
			for (int k = i; k < i + m; k ++) {
				ll af = f[k], ag = g[k], bf = f[k + m], bg = g[k + m];
				f[k] = af * bf % mod;
				g[k] = ag * bg % mod;
				f[k + m] = af * bg % mod;
				g[k + m] = ag * bf % mod;
			}
	}
}

int main () {
	int N = 1 << 17;
	std::fill(f, f + N, 1);
	std::fill(g, g + N, 1);

	int n = read;
	while (n --) {
		int a = read, b = read;
		(f[a] *= 1 + b) %= mod;
		(g[a] *= mod + 1 - b) %= mod;
	}

	F_WTF_T(N);

	ll ans = 0;
	for (int i = 0; i < N; i ++) ans += f[i];
	ans %= mod;
	(ans *= mod - (mod - 1) / N) %= mod;
	-- ans;
	if (ans < 0) ans += mod;
	printf("%lld\n", ans);
}
