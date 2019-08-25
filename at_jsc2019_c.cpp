#if 0
2019.08.25

如果 W 出现在奇数位（编号从 1 开始）上，那么它一定作为一个操作的右端点。
证明：假设 s[i] = W 出现在某操作的左端点，
那么 s[i] 被翻成 B ，必须有奇数个小于 i 的 l 和大于 i 的 r 构成的操作序列，
那么 i 左边剩下的与大于 i 的没有关联的一定是奇数个，
奇数个点无法保证每个点在操作序列中，得出矛盾，原命题成立。

同理，如果 W 出现在偶数位必须是左端点，
B 出现在奇数位必须是左端点，出现在偶数位则相反。

那么就可以确定每个点是作为 l 或者 r ，
剩下的问题就是求把 l 与 r 的问题一一匹配的方案数，
假设操作序列无序，那么就是括号匹配，乘上 n! 即可得出有序的方案数。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, mod = 1000000007;
char s[maxn << 1];

int main() {
	int n = input();
	scanf("%s", s + 1);

	lolong ans = 1;
	int l = 0;

	for(int i = 1; i <= (n << 1); i ++)
		if((s[i] == 'W') == (i & 1))
			(ans *= (l --)) %= mod;
		else
			l ++;

	for(int i = 1; i <= n; i ++)
		(ans *= i) %= mod;

	printf("%lld\n", (l == 0) * ans);
}
