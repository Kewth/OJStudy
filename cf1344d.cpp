#if 0
2020.05.12

  设 f_i(x) = x (a_i - x^2) ，是个三次函数，并且在 [0, a_i] 是先增后减的单峰函数。
  先令所有 b 为 f 的峰点，然后将 sum(b) 与 k 作比较，如果比 k 大，那么就要把 b 减小，
考虑 f 的离散导数 f(x - 1) - f(x) ，不难发现其在 0 到峰点之间是单调的，那么一个朴素的
贪心算法就出来了：每次选择 f(x - 1) - f(x) 最大的位置把其 b 减去 1 ，用堆维护这个导数，
复杂度 O(klogn) 。sum(b) 小于 k 的情况类似，这里不单独讨论。
  这个贪心是很好优化的，由于每次从堆里拿出来的 f(x - 1) - f(x) 是不增的，显然可以二分
最后一步拿出来的值。那么问题转换为对于二分的一个值 Y 和每个位置求出最小的满足 f(x - 1)
- f(x) >= X 的点 x 。由于 f(x - 1) - f(x) 也是单调的，这个问题仍然可以通过二分解决，至
此，通过二分套二分就可以在 O(nlog^2V) 的时间解决问题。
  需要特别注意的是对于二分得到的 Y ，可能最后可以拿出多个 Y ，需要减掉多余的。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <queue>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005;
int a[maxn], b[maxn], c[maxn];

ll R (int i, ll x) {
	return - 3 * x * x - 3 * x + a[i] - 1;
}

ll L (int i, ll x) {
	return + 3 * x * x - 3 * x - a[i] + 1;
}

bool check (int n, ll x, ll d) {
	if (d < 0) {
		for (int i = 1; i <= n; i ++) {
			int l = 0, r = b[i];
			while (l < r) {
				int mid = (l + r) >> 1;
				if (L(i, mid + 1) >= x) r = mid;
				else l = mid + 1;
			}
			c[i] = l;
		}
		for (int i = 1; i <= n; i ++)
			d += b[i] - c[i];
		return d >= 0;
	}
	if (d > 0) {
		for (int i = 1; i <= n; i ++) {
			int l = b[i], r = a[i];
			while (l < r) {
				int mid = (l + r + 1) >> 1;
				if (R(i, mid - 1) >= x) l = mid;
				else r = mid - 1;
			}
			c[i] = r;
		}
		for (int i = 1; i <= n; i ++)
			d += b[i] - c[i];
		return d <= 0;
	}
	return 0;
}

int main () {
	int n = read;
	ll k = read;
	for (int i = 1; i <= n; i ++) {
		read(a[i]);
		b[i] = int(sqrt(a[i] / 3));
		while (b[i] > 0 and L(i, b[i]) > 0) -- b[i];
		while (b[i] < a[i] and R(i, b[i]) > 0) ++ b[i];
		k -= b[i];
	}

	if (k == 0) {
		for (int i = 1; i <= n; i ++)
			printf("%d ", b[i]);
		puts("");
		return 0;
	}

	ll l = - 4000000000000000000, r = 0;
	while (l < r) {
		ll mid = (l + r + 1) >> 1;
		if (check(n, mid, k)) l = mid;
		else r = mid - 1;
	}

	check(n, l, k);
	for (int i = 1; i <= n; i ++)
		k += b[i] - c[i];
	for (int i = 1; i <= n; i ++) {
		while (k < 0 and c[i] > 0 and R(i, c[i] - 1) == l)
			-- c[i], ++ k;
		while (k > 0 and c[i] < a[i] and L(i, c[i] + 1) == l)
			++ c[i], -- k;
	}

	for (int i = 1; i <= n; i ++)
		printf("%d ", c[i]);
}
