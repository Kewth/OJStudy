#if 0
2019.10.06

干，如果我容斥再学好那么一点就可以在 AGC 上 A 掉这题了。

一次操作实际就是将 01 串的最后一位翻转后移动到最前面，
那么任何 01 串都能在 2n 次操作后恢复。
那么什么 01 串能在小于 2n 次操作后恢复？
具体的推证略去，事实上一定要存在 k < n 满足以下几点：
1) k 是 n 的因子，且 n / k 是奇数
2) 将 01 串分成 n / k 段，相邻两段互为取反
此时该串能在 2k 次操作后恢复，并且逆命题同样成立。
不难发现 k = n 时同样可以适应上面的条件，
因此，一个 01 串的最小操作次数为满足条件的最小 2k 。

现在考虑统计，明显数位 DP 的套路，
从左到右每次扫到一个 1 就考虑该位选 0 ，前面不变，后面随便的情况的贡献。
枚举可能的每个 k ，若当前扫到的是第 i 位为 1 ，分类讨论，
1) 如果 i <= k ，那么第 i + 1 位到第 k 位随便选，后面的就是不断取反的 n / k 段，
那么贡献就是 2^(k - i) * k * 2 。
2) 否则 k < i ，如果前 i - 1 位加上 0 正好满足 k 的限制的话，那也是有贡献的，
此时由于前 k 位已经确定，后面同样是确定的，贡献为 k * 2 ，
判断是否有贡献的方法可以预处理每个 t[k] 表示满足 k 限制的最大前缀，
那么这种情况有贡献当且仅当 t[k] = i - 1 。

然而上述方法是会算重的，不难发现若某个 01 串的贡献为 2k ，
上述方法会将所有满足 k | x 的 2x 算入贡献，
因为一个 01 串满足 k 的限制也一定能满足 k 的整数倍的限制，
考虑容斥，记 k 的贡献系数为 a[k] 而不是单纯的 2k ，
从大到小计算 a[k] ，每次减去 k 的整数倍 x 的所有 a[x] 即可。

另外，上述方法无法统计到恰输入串本身的贡献，特殊考虑即可。
#endif
#include <cstdio>
#include <cassert>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005, mod = 998244353;
char s[maxn];
int X[maxn];
int to[maxn];
lolong p2[maxn];
lolong a[maxn];

lolong power(lolong x, int k) {
	if(k < 0) k += mod - 1;
	lolong res = 1;
	while(k) {
		if(k & 1) (res *= x) %= mod;
		(x *= x) %= mod;
		k >>= 1;
	}
	return res;
}

int main() {
	int n = input();
	scanf("%s", s + 1);

	p2[0] = 1;
	for(int i = 1; i <= n; i ++)
		p2[i] = (p2[i - 1] << 1) % mod;

	int p = 0;
	for(int x = 1; x * x <= n; x ++)
		if(!(n % x)) {
			if((n / x) & 1)
				X[++ p] = x;
			if(x & 1 and x * x != n)
				X[++ p] = n / x;
		}

	std::sort(X + 1, X + p + 1);

	for(int k = 1; k <= p; k ++) {
		int x = X[k];
		int &t = to[x];
		t = x;
		while(t < n and s[t + 1] != s[t + 1 - x])
			t ++;
		/* debug("%d -> %d\n", x, t); */
	}

	for(int k = p; k; k --) {
		int x = X[k];
		a[x] = x << 1;
		for(int l = k + 1; l <= p; l ++) {
			int y = X[l];
			if(!(y % x))
				a[x] += mod - a[y];
		}
		a[x] %= mod;
		/* debug("%d : %lld\n", x, a[x]); */
	}

	lolong ans = 0;

	for(int i = 1; i <= n; i ++)
		if(s[i] == '1') {
			for(int k = 1; k <= p; k ++) {
				int x = X[k];
				if(i <= x) {
					/* for(int l = 1; l <= p; l ++) */
					/* 	if(!(X[l] % x)) */
					/* 		assert(i <= X[l] or to[X[l]] == i - 1); */
					/* debug(">%d %d %lld\n", i, x, p2[x - i]); */
					ans += a[x] * p2[x - i] % mod;
				}
				else if(to[x] == i - 1) {
					/* for(int l = 1; l <= p; l ++) */
					/* 	if(!(X[l] % x)) */
					/* 		assert(to[X[l]] == i - 1 or i <= X[l]); */
					/* debug(">>%d %d\n", i, x); */
					ans += a[x];
				}
			}
			ans %= mod;
			/* debug("%lld\n", ans); */
		}

	for(int k = 1; k <= p; k ++)
		if(to[X[k]] == n)
			ans += a[X[k]];
	ans %= mod;

	printf("%lld\n", ans);
}
