#if 0
2019.09.05

多重背包 + 二进制拆分模板。
利用 1, 2, 4, 8, ... 2^n 的子集和可以表示出 [1, 2^(n+1) ) 的性质，
每个数量为 c[i] 的物品可据此拆成 log(c[i]) 个物品以压缩状态。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 105, maxm = 100005;
int a[maxn], c[maxn];
int v[maxn * 10];
bool f[maxm];

int main() {
	int n = input(), m = input();
	if(n == 0 and m == 0)
		return 0;

	for(int i = 1; i <= n; i ++)
		a[i] = input();
	for(int i = 1; i <= n; i ++)
		c[i] = input();

	int p = 0;

	for(int i = 1; i <= n; i ++) {
		int x = 1;
		while(x <= c[i]) {
			v[++ p] = a[i] * x;
			c[i] -= x;
			x <<= 1;
		}
		if(c[i])
			v[++ p] = a[i] * c[i];
	}

	for(int i = 1; i <= m; i ++)
		f[i] = false;

	f[0] = true;
	for(int i = 1; i <= p; i ++)
		for(int j = m; j >= v[i]; j --)
			if(f[j - v[i]])
				f[j] = true;

	/* for(int i = 1; i <= p; i ++) */
	/* 	debug(" %d", v[i]); */
	/* debug("\n"); */
	/* for(int i = 1; i <= m; i ++) */
	/* 	debug("%d", f[i]); */
	/* debug("\n"); */

	int ans = 0;
	for(int i = 1; i <= m; i ++)
		if(f[i])
			ans ++;

	printf("%d\n", ans);

	main();
}
