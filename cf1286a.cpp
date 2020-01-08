#if 0
2020.01.08

一个贪心做法。
首先排列只需要考虑奇偶性，设未确定的数中有 a 个奇数 b 个偶数。
对于两个中间全是 0 的已经确定的数，考虑怎样安排中间的 0 能使答案尽量小。
设这两个数模 2 为 x, y ，中间有 k 个数未确定。

分类讨论。
如果 x != y ，无论中间放什么数，都可以调整位置使得对答案贡献恰好为 1 。
如果 x = y ，那么中间如果能全部放与 x, y 奇偶性相同的数就不会增加答案，
但这样会付出一定代价，代价就是必须用 k 个 a （或 b ）。
而如果中间不全部放与 x, y 奇偶性相同的数的话，无论放什么数，
都可以调整位置使得对答案恰好贡献 2 。

那么不难发现需要决策的部分只有 x = y 中间全放一样的数这种情况，
而且有代价和收益，收益都是 2 ，代价不等。
将这些决策按代价排序，尽量选择代价小的去填，即可得到最大收益，即最小答案。

边界问题在于一些前缀 0 和一些后缀 0 难以判断，
直接暴力枚举钦定 p[0] 和 p[n + 1] 的奇偶性即可。

复杂度 O(n) ，排序部分用基数排序。

然而这题 n 只有 100 。。。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 105;
int p[maxn], tot[2];
int q[2][maxn];

int solve(int n) {
	int las = 0;
	int res = 0;
	for(int i = 1; i <= n + 1; i ++)
		if(p[i]) {
			if(p[i] == p[las])
				++ q[p[i] - 2][i - las - 1];
			else
				++ res;
			las = i;
		}

	for(int i = 0; i < 2; i ++) {
		int max = tot[i];
		for(int x = 0; x <= max; x ++) {
			while(q[i][x] and x <= max) {
				max -= x;
				-- q[i][x];
			}
		}
	}

	for(int i = 0; i <= n; i ++) {
		res += 2 * (q[0][i] + q[1][i]);
		q[0][i] = q[1][i] = 0;
	}

	return res;
}

int main() {
	int n = read;
	if(n == 1) return puts("0"), 0;

	tot[0] = n >> 1;
	tot[1] = (n + 1) >> 1;

	for(int i = 1; i <= n; i ++) {
		int x = read;
		if(x) {
			p[i] = 2 + (x & 1);
			-- tot[p[i] - 2];
		}
	}

	int ans = 1000000000;
	for(int i = 2; i <= 3; i ++)
		for(int j = 2; j <= 3; j ++) {
			p[0] = i;
			p[n + 1] = j;
			ans = std::min(ans, solve(n));
		}

	printf("%d\n", ans);
}
