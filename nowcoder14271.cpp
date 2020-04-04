#if 0
2020.02.22

设 f(n) 表示 n! 末尾 0 的个数。
首先有个性质：将 n! 质因数分解，5 的指数不会超过 2 的指数。
那么 n! 末尾 0 的个数就是 n! 质因数分解后 5 的指数。
也就有 f(n) = floor(n / 5) + f(floor(n / 5)) 。
换言之，f(n) 的值就是 n 的 5 进制表示的带权数位和，其中第 i 个数位的权为 i 。
（从 0 开始算）

那么问题就是计算 0 到 n 中有多少数满足 f(x) % 2 = 0 。
5 进制下的数位 DP 可以很好处理，具体 DP 略。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxk = 60;
int a[maxk];
ll f[maxk][2];

int main() {
	while(1) {
		ll n = read;
		if(n == -1) return 0;

		int p = 0;
		++ n;
		while(n) {
			a[++ p] = n % 5;
			n /= 5;
		}

		f[0][0] = 1;
		for(int i = 1; i <= p; i ++)
			if(i & 1) {
				f[i][0] = f[i - 1][0] * 5;
				f[i][1] = f[i - 1][1] * 5;
			} else {
				f[i][0] = f[i - 1][0] * 3 + f[i - 1][1] * 2;
				f[i][1] = f[i - 1][0] * 2 + f[i - 1][1] * 3;
			}

		ll ans = 0;
		int tag = 0;
		for(int i = p; i; i --) {
			int x = a[i];
			for(int x = 0; x < a[i]; x ++)
				ans += f[i - 1][(!(i & 1) and (x & 1)) ^ tag];
			if(!(i & 1) and (x & 1))
				tag = !tag;
		}

		printf("%lld\n", ans);
	}
}
