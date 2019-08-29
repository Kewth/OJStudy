#if 0
2019.08.29

众所周知（删掉）a 经过 FWT 或变换后的 b 满足 b[S] = sum{T|S=S} a[T] 。
而本题经过找规律或者归纳可以得出 f[S] = xor{T|S=S} a[T] 。
那么魔改 FWT ，把变换中的加法换成异或即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 8000005;
lolong a[maxn << 1];

void FWT(lolong *x, int n) {
	for(int m = 1; m < n; m <<= 1)
		for(int i = 0; i < n; i += (m << 1))
			for(int k = i; k < i + m; k ++)
				x[k + m] ^= x[k];
}

int main() {
	int n = input(), aa = input(), b = input(), c = input(), d = input();

	a[0] = aa;
	for(int i = 1; i < n; i ++)
		a[i] = (a[i - 1] * a[i - 1] + a[i - 1] * b + c) % d;

	int len = 1;
	while(len < n)
		len <<= 1;

	/* for(int i = 0; i < len; i ++) */
	/* 	debug(" %lld", a[i]); */
	/* debug("\n"); */

	FWT(a, len);

	/* for(int i = 0; i < len; i ++) */
	/* 	debug(" %lld", a[i]); */
	/* debug("\n"); */

	lolong ans = 0;
	for(int i = 0; i < n; i ++)
		ans ^= a[i] * (i + 1);
	printf("%lld\n", ans);
}
