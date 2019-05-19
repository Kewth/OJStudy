#if 0
2019.05.19

考虑枚举 a ，计算有多少 b 满足 (a, b) 满足条件。
那么就是 a + P, a + 2P, a + 3P, ... 在 B 的数量。
考虑建出一张 Q 个点的图 i -> (i + P) % Q 。
这张图一定由若干个环组成。

枚举 a ，先算出 a + kP 在环上跑了多少次循环，
再考虑剩余部分的贡献，剩余部分一定是环的一个连续的子链，
只要对环上的信息做一个前缀和维护即可。
#endif
#include <cstdio>
#define _ 1ll *
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
const int maxn = 1000050;
int loop_len[maxn], loop_val[maxn], loop_end[maxn];
int a[maxn], b[maxn];
bool in_b[maxn];

int main() {
	int p, q, n, m;
	lolong max;
	scanf("%d %d %d %d %lld", &p, &q, &n, &m, &max);
	max --;
	for(int i = 1; i <= n; i ++)
		scanf("%d", a + i);
	for(int i = 1; i <= m; i ++) {
		scanf("%d", b + i);
		in_b[b[i]] = true;
	}
	for(int i = 0; i < q; i ++)
		if(not loop_len[i]) {
			loop_len[i] = 1;
			loop_val[i] = in_b[i];
			loop_end[i] = (i - p % q + q) % q; // - p + q 可能还是负数
			for(int j = (i + p) % q; j != i; j = (j + p) % q) {
				loop_len[j] = loop_len[(j - p % q + q) % q] + 1;
				loop_val[j] = loop_val[(j - p % q + q) % q] + in_b[j];
				loop_end[j] = loop_end[(j - p % q + q) % q];
			}
		}
	lolong ans = 0;
	/* for(int i = 0; i < q; i ++) */
	/* 	debug("%d: %d %d %d\n", i, loop_len[i], loop_val[i], loop_end[i]); */
	for(int i = 1; i <= n; i ++) {
		lolong step = (max - a[i]) / p;
		const int end = loop_end[a[i] % q];
		ans += loop_val[end] * (step / loop_len[end]);
		step %= loop_len[end];
		ans += loop_val[(a[i] + step * p) % q]
			- loop_val[(a[i] - p % q + q) % q];
		if(loop_len[a[i] % q] + step > loop_len[end]
				or loop_len[a[i] % q] == 1)
			ans += loop_val[end];
		/* debug("%d: %lld\n", a[i], ans); */
	}
	printf("%lld\n", ans);
}
