#if 0
2019.08.21

考虑枚举答案矩形的左右边界 l, r ，有用的行就是 [l, r] 全 1 的行。
直接做 O(n^3) ，左边界 l 固定时，考虑每次 r ++ 的影响，
就是会少一些有用的行，那么对于每个 l 维护有用的行，随着 r ++ 一个个删没用的行。
实现上需要排序，复杂度 O(n^2 logn) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1004;
struct Line {
	// 直接开数组见祖宗
	/* int co[maxn]; */
	/* int to[maxn]; */

	int *co, *to;
	Line(): co(new int[maxn]), to(new int[maxn]) {}
};
Line line[maxn];

int cmp_d;
inline bool cmp(Line &a, Line &b) {
	return a.to[cmp_d] > b.to[cmp_d];
}

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= n; i ++) {
		int last = 1;

		for(int j = 1; j <= m; j ++) {
			line[i].co[j] = getchar() - '0';
			while(line[i].co[j] != 0 and line[i].co[j] != 1)
				line[i].co[j] = getchar() - '0';

			if(not line[i].co[j])
				while(last <= j)
					line[i].to[last ++] = j - 1;
		}

		while(last <= m)
			line[i].to[last ++] = m;
	}

	int ans = 0;

	for(int l = 1; l <= m; l ++) {
		cmp_d = l;
		std::sort(line + 1, line + n + 1, cmp);

		int last = n;
		for(int r = l; r <= m; r ++) {
			while(last and line[last].to[l] < r)
				last --;

			if(not last)
				break;

			ans = std::max(ans, (r - l + 1) * last);
		}
	}

	printf("%d\n", ans);
}
