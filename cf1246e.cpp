#if 0
2020.03.31

如果有解，最后每个数的贡献一定是 a[i] / k^b[i] 的形式。
可以归纳证明，b[i] 最大的数一定有至少两个。
假设已经知道了 b ，输出方案，只需要重复将 b[i] 最大的两个数合并即可。
那么问题就是如何求这个 b 。

DP 设 f[S][x] 表示使用 S 集合内的点，是否存在 b 使得 S 内的点的贡献和为 x 。
转移不需要枚举子集，只需要枚举 b = 0 的点即可，
如果不存在 b = 0 的点，那么可以从 f[S][xk] 转移。
用 bitset 优化 f 的第二维，复杂度可以做到 (2^n V) 。
通过 f 可以简单判断是否有解，但是用 bitset 压位后不能记转移方向，需要倒推一遍得到 b 。
#endif
#include <cstdio>
#include <algorithm>
#include <bitset>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;
typedef size_t si;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 16, maxk = 2048;
int a[maxn], b[maxn];
std::bitset<maxk> f[1 << maxn], g[1 << maxn];

int main () {
	int n = read, k = read;
	for (int i = 0; i < n; i ++) read(a[i]);

	f[0][0] = 1;
	for (int S = 1; S < (1 << n); S ++) {
		for (int i = 0; i < n; i ++)
			if (S >> i & 1)
				f[S] |= f[S ^ (1 << i)] << si(a[i]);
		for (int x = (maxk - 1) / k; x >= 0; x --)
			if (f[S][si(x * k)] and !f[S][si(x)])
				f[S][si(x)] = g[S][si(x)] = 1;
	}

	int S = (1 << n) - 1, x = 1;
	if (!f[S][si(x)]) return puts("NO"), 0;
	puts("YES");

	while (S) {
		while (g[S][si(x)]) {
			x *= k;
			for (int i = 0; i < n; i ++)
				if (S >> i & 1)
					++ b[i];
		}
		for (int i = 0; i < n; i ++)
			if (x >= a[i] and S >> i & 1 and f[S ^ (1 << i)][si(x - a[i])]) {
				S ^= 1 << i;
				x -= a[i];
				break;
			}
	}

	std::priority_queue<par> q;
	for (int i = 0; i < n; i ++) q.push(par(b[i], a[i]));

	while (q.size() > 1) {
		par p1 = q.top(); q.pop();
		par p2 = q.top(); q.pop();
		if (p1.first != p2.first) return 1;
		printf("%d %d\n", p1.second, p2.second);
		p1.second += p2.second;
		while (p1.second % k == 0)
			-- p1.first, p1.second /= k;
		q.push(p1);
	}
}
