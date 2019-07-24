#if 0
2019.07.24

分治，取中点后把两边成了子问题，
问题转换为统计跨越中点的区间的权值和。
从中点向两边求出前缀最值，
向左边枚举点 i ，维护右边的 x, y 满足：
x 是 rmin[x] >= lmin[i] 中最大的，
y 是 rmax[y] <= lmax[i] 中最小的。
由于 lmin, lmax, rmin, rmax 具有单调性， i 左移的过程中可以容易维护 x, y 的值。
考虑统计 i 为左端点的所有区间权值和，分三类讨论：
1) 右端点小于 x, y ，那么 min, max 只由左边的 i 决定，是个定值。
2) 右端点在 x, y 之间，那么 min, max 有一个由左边决定，一个由右边决定。
3) 右端点大于 x, y ，那么 min, max 都由右边决定。
分别进行一些前缀和预处理即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 500005, mod = 1000000000;
lolong a[maxn];
lolong lmin[maxn], lmax[maxn], rmin[maxn], rmax[maxn];
lolong rminsum[maxn], rmaxsum[maxn], rmmsum[maxn];
lolong rminsum2[maxn], rmaxsum2[maxn], rmmsum2[maxn];

lolong calc(int l, int r) {
	if(l == r)
		return a[l] * a[r];
	int mid = (l + r) >> 1;
	lolong res = calc(l, mid) + calc(mid + 1, r);
	debug("calc %d-%d\n", l, r);
	int L = mid - l + 1, R = r - mid;
	for(int i = 1; i <= L; i ++) {
		lmin[i] = std::min(lmin[i - 1], a[mid - i + 1]);
		lmax[i] = std::max(lmax[i - 1], a[mid - i + 1]);
	}
	for(int i = 1; i <= R; i ++) {
		rmin[i] = std::min(rmin[i - 1], a[mid + i]);
		rmax[i] = std::max(rmax[i - 1], a[mid + i]);
		rminsum[i] = (rminsum[i - 1] + rmin[i]) % mod;
		rmaxsum[i] = (rmaxsum[i - 1] + rmax[i]) % mod;
		rminsum2[i] = (rminsum2[i - 1] + rmin[i] * i) % mod;
		rmaxsum2[i] = (rmaxsum2[i - 1] + rmax[i] * i) % mod;
		rmmsum[i] = (rmmsum[i - 1] + rmin[i] * rmax[i]) % mod;
		rmmsum2[i] = (rmmsum2[i - 1] + rmin[i] * rmax[i] % mod * i) % mod;
	}
	int minx = 0, maxx = 0;
	debug("%lld\n", res);
	for(int i = 1; i <= L; i ++) {
		while(minx < R and rmin[minx + 1] >= lmin[i])
			minx ++;
		while(maxx < R and rmax[maxx + 1] <= lmax[i])
			maxx ++;
		debug("%d: %d, %d\n", i, minx, maxx);
		int x = std::min(minx, maxx), y = std::max(minx, maxx);
		res += lmin[i] * lmax[i] % mod * ((lolong(i + 1 + i + x) * x >> 1) % mod) % mod;
		debug(" a %lld\n", res);
		if(minx == x)
			res += lmax[i] *
				((i * (rminsum[y] + mod - rminsum[x]) + rminsum2[y] + mod - rminsum2[x]) % mod) % mod;
		else
			res += lmin[i] *
				((i * (rmaxsum[y] + mod - rmaxsum[x]) + rmaxsum2[y] + mod - rmaxsum2[x]) % mod) % mod;
		debug(" b %lld\n", res);
		res += (i * (rmmsum[R] + mod - rmmsum[y]) + rmmsum2[R] + mod - rmmsum2[y]) % mod;
		debug(" c %lld\n", res);
	}
	return res % mod;
}

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	lmin[0] = rmin[0] = 1000000000;
	printf("%lld\n", calc(1, n));
}

