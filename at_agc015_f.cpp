#if 0
2020.01.11

以下二元组 (i, j) 均只考虑 i < j 的情况，询问假定 x < y 。

设 g[x][y] 为范围内最大值，即第一个答案。
g[x][y] 是很好算的，根据 (i=F[k], j=F[k + 1]) 是满足 f[i][j] = k 的最小二元组可以知道。
其中 F[k] 表示第 k 个斐波那契数。

称满足 f[i][j] = g[i][j] = k 的二元组 (i, j) 为 good pair of k 。
那么第二个答案就只需要统计范围内的 good pair of g[x][y] ，i = j 的另算。

然而 good pair 的数量巨大，比如所有 (i=1, j>1) 都是 good pair of 1 。
但注意到许多 good pair 经过一次 gcd 后就会变得一样，
把这些 good pair 缩在一起，用一个最小的来表示，称作 excellent pair 。
形式化的，(i, j) 是 excellent pair of k 当且仅当：
1. (i, j) 是 good pair of k
2. j <= 2i
那么 (i, j) 这个 excellent pair 实际上就代表了 (i, j), (i, j + i), (i, j + 2i) ...
这些 good pair 。

excellent pair 的数量是很少的，excellent pair of 只有恰好 k 个。
考虑怎么预处理 excellent pair ，
excellent pair 经过一次 gcd 后一定是一个 good pair ，
通过 excellent pair of k ，每个 (i, j) 改为 (j, i + j) 就是一个新的 excellent pair of k + 1 ，
另外还会多出来一个 excellent of k + 1 是 (F[k + 2], F[k] + F[k + 2]) 。
#endif
#include <cstdio>
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<ll, ll> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxk = 100, mod = 1000000007;
ll fi[maxk];
std::vector<par> excellent[maxk];

int main() {
	int k = 1;
	fi[0] = fi[1] = 1;
	ll lim = 1000000000000000000;
	while(fi[k] + fi[k - 1] <= lim) {
		++ k;
		fi[k] = fi[k - 1] + fi[k - 2];
	}

	excellent[1].push_back(par(1, 2));
	for(int i = 2; i <= k; i ++) {
		for(par p : excellent[i - 1])
			excellent[i].push_back(par(p.second, p.first + p.second));
		excellent[i].push_back(par(fi[i + 1], fi[i + 1] + fi[i - 1]));
	}

	int q = read;
	while(q --) {
		ll x = read, y = read;
		if(x > y) std::swap(x, y);

		int max = 1;
		while(max + 2 <= k and fi[max + 1] <= x and fi[max + 2] <= y)
			++ max;

		/* debug("q\n"); */
		ll tot = 0;
		for(par p : excellent[max]) {
			/* debug("%lld %lld\n", p.first, p.second); */
			if(p.first <= x and p.second <= y)
				tot += (y - p.second) / p.first + 1;
			if(p.second <= x)
				tot += (x - p.second) / p.first + 1;
			tot %= mod;
		}

		if(max == 1)
			tot += x;

		printf("%d %lld\n", max, tot);
	}
}
