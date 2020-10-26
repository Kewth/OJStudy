/*
 * Author: Kewth

 * Date:
  2020.10.16

 * Solution:
 * Hall 定理，双指针

  对于点集 S 考虑判断是否存在匹配覆盖了 S 。如果 S 只包含左边的点或者只包含右边的点，
容易发现用 Hall 定理就能判断。否则设 S = X | Y ，其中 X, Y 分别是左右边集。那么可以证
明，存在匹配覆盖 S 当且仅当存在匹配覆盖 X 且存在匹配覆盖 Y 。

  必要性很显然，证明充分性，假设已知一个覆盖 X 的匹配和一个覆盖 Y 的匹配，考虑取构造
一个覆盖 S 的匹配，首先把覆盖 X 的匹配作为初始匹配，然后逐个加入 Y 中的点和对应的匹配
点，分类讨论不难得到一个简单的构造方法。

  那么把两边的能被匹配覆盖的点集分别处理出来然后双指针即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 20;
char s[maxn + 1];
int al[1 << maxn], bl[1 << maxn];
bool af[1 << maxn], bf[1 << maxn];
int as[1 << maxn], bs[1 << maxn];
std::vector<int> A, B;

inline int count (int x) { return __builtin_popcount(unsigned(x)); }

int main () {
	int n = read, m = read;
	for (int i = 0; i < n; i ++) {
		scanf("%s", s);
		for (int j = 0; j < m; j ++)
			if (s[j] == '1') {
				al[1 << i] |= 1 << j;
				bl[1 << j] |= 1 << i;
			}
	}

	for (int i = 0; i < n; i ++) read(as[1 << i]);
	for (int i = 0; i < m; i ++) read(bs[1 << i]);
	int min = read;

	for (int S = 0; S < (1 << n); S ++) {
		al[S] = al[S & (S - 1)] | al[S & -S];
		as[S] = as[S & (S - 1)] + as[S & -S];
		af[S] = count(al[S]) >= count(S);
		for (int i = 0; i < n; i ++)
			if (S >> i & 1)
				af[S] &= af[S ^ (1 << i)];
		if (af[S]) A.push_back(as[S]);
	}

	for (int S = 0; S < (1 << m); S ++) {
		bl[S] = bl[S & (S - 1)] | bl[S & -S];
		bs[S] = bs[S & (S - 1)] + bs[S & -S];
		bf[S] = count(bl[S]) >= count(S);
		for (int i = 0; i < m; i ++)
			if (S >> i & 1)
				bf[S] &= bf[S ^ (1 << i)];
		if (bf[S]) B.push_back(bs[S]);
	}

	std::sort(A.begin(), A.end());
	std::sort(B.begin(), B.end());

	ll ans = 0;
	auto it = B.end();
	for (int x : A) {
		while (it != B.begin() and x + *(it - 1) >= min)
			-- it;
		ans += B.end() - it;
	}
	printf("%lld\n", ans);
}
