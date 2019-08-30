#if 0
2019.08.30

考虑最小的边 e，把树分成两部分 T1, T2 ，
由于一定要有跨过 T1, T2 的路径，e 至少会贡献一次，
那么分成两个子问题，在 T1, T2 中分别找出最优排列，合并起来就会加 e 的贡献。
这样一定是最优的，考虑证明 e 贡献次数大于 1 的时候答案一定不会变大。
假设 e 贡献两次，那么最优的方案就是在 T1, T2 中找出 3 个排列合并，
T1, T2 至少要有一个排列，那么这三个排列合并加上 2e 的贡献，
但是贡献中一定少了 T1 的一条边或者 T2 的一条边，而该边一定不比 e 小，所以答案一定没有增加。
那么同理 e 贡献 3 次时答案一定不比贡献 2 次优，由此归纳出上述结论。
因此答案就是所有边权和。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

int main() {
	int n = input() - 1;
	lolong ans = 0;
	while(n --) {
		input();
		input();
		ans += input();
	}
	printf("%lld\n", ans);
}
