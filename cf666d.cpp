#if 0
2020.02.04

枚举每个点是走横坐标还是走纵坐标，得到 4 条直线，
要求放置的每个点要占据一条直线，将直线去重，分类讨论：

1) 两条横线两条竖线
放置的点一定是四个交点，判断一下是否是正方形然后统计。
统计的话直接 4! 枚举点之间的配对方式即可。

2) 两条横线一条竖线（一条横线两条竖线同）
首先两个交点一定要放，那么确定了正方形边长为两条横线的距离。
枚举剩下两个点在左边还是右边，分别统计。

3) 两条横线（两条竖线同）
四个点都要放在两条平行线上，显然一条直线放两个点，
那么可以确定正方形边长 D ，两个横坐标是形如 x 和 x + D 这样的，
求出最优的 x ，一个简单的方式是三分，
因为不难发现答案是关于 x 的单峰函数。
更优秀的方式是直接解式子，
设第一条直线原有的两个点横坐标为 x1, x2 ，另外一条为 x3, x4 。
在每条直线上枚举配对方式，
不妨设 x1, x2, x3, x4 分别与 x, x + D, x, x + D 配对。
那么这部分的答案就是 max(|x1 - x|, |x2 - x - D|, |x3 - x|, |x4 - x - D|) ，
令 x5 = x2 - D, x6 = x4 - D ，上式为
max(|x1 - x|, |x5 - x|, |x3 - x|, |x6 - x|)
也就是数轴上 x 到四个位置的距离的最大值，
取这四个位置的最大最小值的平均数即可令这个值最小。

至于其他情况都是不合法的。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

int calc(int *x, int *y, int *nx, int *ny, int *ansp) {
	int p[4] = {0, 1, 2, 3}, res = 1000000000;
	do {
		int now = 0;
		for(int i = 0; i < 4; i ++)
			if(x[i] == nx[p[i]])
				now = std::max(now, std::abs(y[i] - ny[p[i]]));
			else if(y[i] == ny[p[i]])
				now = std::max(now, std::abs(x[i] - nx[p[i]]));
			else
				now = 1000000000;
		if(now < res) {
			res = now;
			for(int i = 0; i < 4; i ++) ansp[i] = p[i];
		}
	} while(std::next_permutation(p, p + 4));
	return res;
}

int main() {
	const int _ = 20200202; // magic
	int T = read;

	while(T --) {
		int x[5], y[5];
		for(int i = 0; i < 4; i ++) {
			x[i] = read;
			y[i] = read;
		}
		x[4] = 1;
		y[4] = 0;

		int ans = 1000000000;

		int ansx[4], ansy[4];
		int nx[4], ny[4];

		auto update = [&]() {
			int p[4] = {0, 1, 2, 3};
			int tmp = calc(x, y, nx, ny, p);
#if 0
			debug(">>>  get %d\n", tmp);
			for(int i = 0; i < 4; i ++)
				debug("%d %d\n", nx[p[i]], ny[p[i]]);
#endif
			if(tmp < ans) {
				ans = tmp;
				if(x[4] == 1)
					for(int i = 0; i < 4; i ++) {
						ansx[i] = nx[p[i]];
						ansy[i] = ny[p[i]];
					}
				if(x[4] == 0)
					for(int i = 0; i < 4; i ++) {
						ansx[i] = ny[p[i]];
						ansy[i] = nx[p[i]];
					}
			}
		};

		for(int S = 0; S < 16; S ++) {
			int xx[4] = {_, _, _, _}, yy[4] = {_, _, _, _};
			for(int i = 0; i < 4; i ++) {
				int *tar = (S >> i & 1) == x[4] ? xx : yy;
				int v = (S >> i & 1) == x[4] ? x[i] : y[i];
				int j = 0;
				while(tar[j] != _ and tar[j] != v) ++ j;
				tar[j] = v;
			}

			if(xx[2] != _ or yy[2] != _) continue;
			if(xx[1] == _ and yy[1] == _) continue;

			if(yy[0] == _) {
				std::swap(xx, yy);
				std::swap(x, y);
			}

			if(xx[0] == _) {
				int d = std::abs(yy[0] - yy[1]);
				ny[0] = ny[2] = yy[0];
				ny[1] = ny[3] = yy[1];

				for(int T = 0; T < 4; T ++) {
					int shit[2] = {T >> 1, T & 1};
					int l = 1000000000, r = - 1000000000;
					for(int i = 0; i < 4; i ++) {
						int o = y[i] == yy[1];
						int v = shit[o] ? x[i] + d : x[i];
						shit[o] ^= 1;
						l = std::min(l, v);
						r = std::max(r, v);
					}

					// debug("fcuk %d %d %d\n", d, l, r);
					int mid = (l + r + 1) >> 1;
					nx[0] = nx[1] = mid;
					nx[2] = nx[3] = mid - d;
					update();
				}
				continue;
			}

			if(yy[1] == _) {
				std::swap(xx, yy);
				std::swap(x, y);
			}

			if(xx[1] == _) {
				int d = std::abs(yy[0] - yy[1]);
				nx[0] = nx[1] = xx[0];
				ny[0] = ny[2] = yy[0];
				ny[1] = ny[3] = yy[1];

				nx[2] = nx[3] = xx[0] - d;
				update();
				nx[2] = nx[3] = xx[0] + d;
				update();
				continue;
			}

			if(std::abs(xx[0] - xx[1]) == std::abs(yy[0] - yy[1])) {
				nx[0] = nx[1] = xx[0];
				nx[2] = nx[3] = xx[1];
				ny[0] = ny[2] = yy[0];
				ny[1] = ny[3] = yy[1];
				update();
			}
		}

		if(ans == 1000000000) puts("-1");
		else {
			printf("%d\n", ans);
			for(int i = 0; i < 4; i ++)
				printf("%d %d\n", ansx[i], ansy[i]);
		}
	}
}
