/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.04

 * Solution:
    二分答案 x ，那么不妨让每一条选取的直线到 O 的距离恰好为 x ，也就是与半径为 x 的
圆 O 相切，这样一来选取的一条直线就可以用圆上的一个切点来表示。

    对于圆外每个点 P ，相当于一个限制，考虑什么样的直线能够保护点 P ，这样的直线对应
的切点构成了圆上的一个弧，那么点 P 的限制就相当于在一个弧内至少要有一个点被选。于是就
有 n 条弧，要在圆上选 m 个点使得每条弧内都至少有一个点。

    不妨假设弧两两不包含，每个弧对应一个极角区间 [l, r] ，由于极角的取值实际是环，将
环复制一遍，也就是把 [l + 2PI, r + 2PI] 也考虑进去，把所有 2n 个区间按左端点排序，一
个很重要的性质是任意连续 n 个区间原来对应的弧一定都是不同的（弧两两不包含）。

    环完美地转换为序列后问题就很好处理了，不妨把选取的 m 个点都放在区间的右端点，那么
设 f[0][i] 表示选取第 i 个区间的右端点，下一个未覆盖该点的区间，然后倍增地处理出所有形
如 f[k][i] 的东西，就可以很容易对于每个区间求出贪心地选 m 个点后是否能选 n 个连续的区
间了。

 * Digression:
  这个环转序列我要吐了，因为一开始没有注意到上述的“很重要的性质”想了很久。

 * CopyRight:
          ▁▃▄▄▄▃▃▃▃▄▶
        ▗▇▀▔    ▔▔▔▔
       ▄▛   ▃▅━━■▄▂
      ▟▊   ▐▘     ▀▙
     ▟▜▌   ▐▖   ▋  ▐▍
    ▟▘ ▜   ▝▀▇▆●▘  ▐▌
  ▗▟▘   ▜▃       ▁▅▛
  ▔▀▼▅▄▃▃██▅▄▄▄▅■▀▔
        ▔▔▔▔▔▔
 */

#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator () (a...); }
} read;

const int maxn = 100005;
struct Shit {
	double l, r;
	int i;
} shit[maxn << 1];
int px[maxn], py[maxn];
double pd[maxn], pa[maxn];
double pi = acos(-1);
bool mark[maxn];
int f[20][maxn];

bool operator < (Shit a, Shit b) { return a.l < b.l; }

bool check (int n, int m, double r) {
	for (int i = 1; i <= n; i ++) {
		double dt = acos(r / pd[i]);
		shit[i] = {pa[i] - dt, pa[i] + dt, i};
	}
	for (int i = 1; i <= n; i ++)
		shit[n + i] = {shit[i].l + pi * 2, shit[i].r + pi * 2, shit[i].i};
	std::sort(shit + 1, shit + n * 2 + 1);

	std::fill(mark, mark + n + 1, 0);
	double max = 1e100;
	for (int i = n * 2; i; i --)
		if (shit[i].r > max)
			mark[shit[i].i] = 1;
		else
			max = shit[i].r;

	int p = 0;
	for (int i = 1; i <= n; i ++)
		if (!mark[i]) {
			double dt = acos(r / pd[i]);
			shit[++ p] = {pa[i] - dt, pa[i] + dt, i};
		}
	for (int i = 1; i <= p; i ++)
		shit[p + i] = {shit[i].l + pi * 2, shit[i].r + pi * 2, shit[i].i};
	std::sort(shit + 1, shit + p * 2 + 1);

	for (int i = 1, j = 1; i <= p * 2; i ++) {
		while (j <= p * 2 and shit[j].l <= shit[i].r)
			++ j;
		f[0][i] = j;
	}

	for (int k = 0; k < 20; k ++)
		f[k][p * 2 + 1] = p * 2 + 1;
	for (int k = 1; k < 20; k ++)
		for (int i = 1; i <= p * 2; i ++)
			f[k][i] = f[k - 1][f[k - 1][i]];

	for (int i = 1; i <= p; i ++) {
		int j = i;
		for (int k = 0; k < 20; k ++)
			if (m >> k & 1)
				j = f[k][j];
		if (j >= i + p)
			return 1;
	}
	return 0;
}

int main () {
	int n = read, m = read;
	double l = 0, r = 1e100;
	for (int i = 1; i <= n; i ++) {
		read(px[i], py[i]);
		pd[i] = sqrt(1ll * px[i] * px[i] + 1ll * py[i] * py[i]);
		r = std::min(r, pd[i]);
		pa[i] = atan2(py[i], px[i]);
	}

	for (int k = 0; k < 64; k ++) {
		double mid = (l + r) / 2;
		if (check(n, m, mid))
			l = mid;
		else
			r = mid;
	}

	printf("%.8lf\n", l);
}
