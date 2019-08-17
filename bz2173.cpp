#if 0
2019.07.31

设 g[i] 为 n = i 时的答案，f 是斐波那契数列，
不难发现 g 的递推式就是类似 f 与 g 卷积的形式，可以分治 FFT 或者求逆爆搞。
但是利用到 f 的特殊性质，把个 g[i] 和 g[i + 1] 加起来，
推一推，可以得到 g 的递推式。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() {
	int c = getchar(), x = 0;
	while(c < '0' or c > '9') c = getchar();
	while(c >= '0' and c <= '9') x = x * 10 + c - '0', c = getchar();
	return x;
}

const int maxn = 1000005, mod = 1000000007;
lolong f[maxn], g[maxn];

int main() {
	int n = input();
	f[0] = 0;
	f[1] = 1;
	g[0] = g[1] = 1;
	g[2] = 2;
	for(int i = 3; i <= n; i ++)
		g[i] = (g[i - 1] * 2 + g[i - 2]) % mod;
	printf("%lld\n", g[n]);
}
