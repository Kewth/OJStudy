#if 0
date +%Y.%m.%d

  先放长度最大的弧，然后根据其位置把环转成链，问题变为连续的线段覆盖问题。
  注意到长度都是整数，那么只要枚举剩下所有弧的位置的小数部分的大小关系，问题就可以转换
为离散的线段覆盖，而所有弧的小数部分是独立同分布随机变量，因此每种大小关系是等概率出现
的。
  既然小数部分的大小关系已经确定，不妨设其为 1/n, 2/n, ... ，那么问题就是在长为 C * n
的链上做离散的线段覆盖问题，DP 设 f[S][i] 表示用 S 集合内的线段，恰好覆盖 [0, i] 的方
案数。不重不漏的转移需要枚举左端点最右边的线段，实现可以直接从小到大枚举左端点，再枚举
状态进行插入线段的转移。
#endif
#include <cstdio>
#include <cstring>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef long double ld;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 6, maxc = 50;
int len[maxn], p[maxn];
ll f[1 << maxn][maxc * maxn + 1];

int main () {
	int n = read, c = read;
	for (int i = 0; i < n; i ++) read(len[i]);
	std::sort(len, len + n);

	ll ans = 0, tot = 0;
	for (int i = 1; i < n; i ++) p[i] = i - 1;
	do {
		int U = (1 << n >> 1) - 1;
		memset(f, 0, sizeof f);
		int min = len[n - 1] * n;
		f[0][min] = 1;
		for (int l = 0, i; l < c * n; l ++)
			if ((i = l % n)) {
				i = p[i];
				int r = std::min(c * n, l + len[i] * n);
				for (int S = 0; S <= U; S ++)
					if (!(S >> i & 1))
						for (int k = l; k <= c * n; k ++)
							f[S | (1 << i)][std::max(k, r)] += f[S][k];
			}
		ans += f[U][c * n];
		++ tot;
	} while (std::next_permutation(p + 1, p + n));

	ld Ans = ans;
	Ans /= tot;
	for (int i = 0; i < n - 1; i ++)
		Ans /= c;
	printf("%.12Lf\n", Ans);
}
