/*
 * Author: Kewth

 * Date:
  2019.07.11

 * Solution:
  根据容斥原理，如果 n 种饮料能恰好装进 n - 1 个瓶子里，那这些瓶子一定合法。
  那么对于饮料集合 S 和瓶子容量 L ，有合法方案当且仅当下面至少一个条件成立：

  1) S 只有一种饮料且该饮料体积为 L 。
  2) S 能恰好装进 |S| - 1 个瓶子里。
  3) S 可以分成若干集合 T 使得每个 T 满足 1) 或 2)

  易得 3) 等价于以下的 4)

  4) 存在 S 的子集 T 使得 T 满足 1) 或 2) 且 S / T 有合法方案。

  可据此枚举答案然后状压 DP 验证。具体地，设 f[S] 表示 S 集合内最多可以找到
多少个不相交的满足条件 2) 的子集，随便转移即可。总复杂度 O(2^n n^2) 。

 * Digression:
  update on 2021.05.18:
  我他妈下巴都惊掉了，这他妈不是 NOI2020 D2T1 的加强版？我他妈 19 年居然做过？
  原题数据水得一匹，旧做法复杂度不对，并且公开的所有 AC 做法都是假的，所以重写
了一遍。

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 21;
ll sum[1 << maxn];
int count[1 << maxn];
int f[1 << maxn];

int main () {
	int n = read;
	for (int i = 0; i < n; i ++)
		read(sum[1 << i]);
	for (int S = 1; S < (1 << n); S ++) {
		sum[S] = sum[S & (S - 1)] + sum[S & -S];
		count[S] = count[S & (S - 1)] + 1;
	}
	ll tot = sum[(1 << n) - 1];

	if (n == 1)
		return puts("1"), 0;

	for (int m = (n + 1) >> 1; m < n; m ++) {
		for (int S = 0; S < (1 << n); S ++) {
			f[S] = 0;
			for (int i = 0; i < n; i ++)
				if (S >> i & 1)
					f[S] = std::max(f[S], f[S ^ (1 << i)]);
			int b = f[S] + 1;
			if (sum[S] * m == (count[S] - b) * tot)
				f[S] = b;
		}
		// 必须是大于等于
		if (f[(1 << n) - 1] >= n - m)
			return printf("%d\n", m), 0;
	}

	puts("-1");
}

