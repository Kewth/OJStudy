#if 0
2020.02.15

考虑贪心一个一个选数加入子序列，每次选贡献最大的点，
直到加入任意一个点都不会使答案变大，即可得到最优答案。

问题在于如何找到贡献最大的点。

注意到第一个数加入子序列得到的贡献可以表达为 y - kx ，
其中 y 是在该数以及该数后面被加入子序列的和，
k 是在该数前面被加入子序列的数量的相反数，
x 就是该数的值。

分块，每一个块内需保证 k 相同，
如果不同只需要把所有 kx 看作常数放进 y 中，然后令 k = 0 即可。
那么对于块内 k 相同的若干 (x, y) ，
只需要求出其上凸壳即可快速得到块内贡献最大的点。

每次询问到贡献最大的点后，在它后面的点 k 减一，前面的 y 加 a ，
其中 a 是该点的值。
对于完整的块可以打标记，零散部分暴力重构即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005, maxs = 400, B = 320;
ll tk[maxs], ty[maxs];
ll x[maxs][B], y[maxs][B];
struct Dot {
	ll x, y, id;
} que[maxs][B], tmp[B];
int front[maxs], size[maxs];

ll query(int b) {
	int &p = front[b];
	while(p + 1 < size[b] and que[b][p].y - tk[b] * que[b][p].x <
			que[b][p + 1].y - tk[b] * que[b][p + 1].x)
		++ p;
	// debug("query %d (k=%lld, ty=%lld) -> (%lld, %lld)\n",
			// b, tk[b], ty[b], que[b][p].x, que[b][p].y);
	return ty[b] + que[b][p].y - tk[b] * que[b][p].x;
}

void build(int b) {
	for(int i = 0; i < B; i ++)
		tmp[i] = {x[b][i], y[b][i], i};
	std::sort(tmp, tmp + B, [](Dot a, Dot b) {
				return a.x == b.x ? a.y < b.y : a.x < b.x;
			});

	int &p = size[b];
	p = 0;
	for(int i = 0; i < B; i ++) {
		while(p > 1 and (que[b][p - 2].y - que[b][p - 1].y) *
				(que[b][p - 1].x - tmp[i].x) <=
				(que[b][p - 1].y - tmp[i].y) *
				(que[b][p - 2].x - que[b][p - 1].x))
			-- p;
		que[b][p ++] = tmp[i];
	}

	// debug("build %d\n", b);
	// for(int i = 0; i < p; i ++)
		// debug("%lld %lld\n", que[b][i].x, que[b][i].y);

	front[b] = 0;
}

int main() {
	int n = read;
	for(int i = 0; i < n; i ++)
		x[i / B][i % B] = y[i / B][i % B] = read;
	int s = (n - 1) / B + 1;

	for(int i = 0; i < s; i ++)
		build(i);

	ll ans = 0;
	while(1) {
		int b = 0;
		for(int i = 1; i < s; i ++)
			if(query(i) > query(b))
				b = i;

		if(query(b) <= 0)
			break;
		ans += query(b);

		int p = que[b][front[b]].id;
		ll a = x[b][p];
		x[b][p] = - 1000000000;
		y[b][p] = - 1000000000000000000;

		for(int i = 0; i < p; i ++)
			y[b][i] += a;
		for(int i = p + 1; i < B; i ++)
			y[b][i] += x[b][i];
		build(b);

		for(int i = 0; i < b; i ++)
			ty[i] += a;
		for(int i = b + 1; i < s; i ++)
			-- tk[i];

		// debug("use %d\n", b * B + p + 1);
	}

	printf("%lld\n", ans);
}
