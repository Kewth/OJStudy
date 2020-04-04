#if 0
2020.02.17

把坐标系旋转 45 度再放缩一下，四个移动向量就变为：
(-1, -1), (1, -1), (-1, 1), (1, 1)
两个维度之间互不影响，分别考虑。

那么问题转换为在数轴上，只有两个移动值： -1 和 1 。
默认都选 -1 ，然后再放缩一下，只有两个移动值：0 和 1 。

假设一个周期的移动距离为 x 。
那么 t 时刻落在位置 p ，设 t = al + b (b < x) ，
就有 p = ax + s[b] ，其中 s[b] 是 b 时刻的位置。
根据 0 <= s[b] <= x ，可以列出关于 x 的不等式。

考虑求出 s 。
将所有 (p, a, b) 按 b 排序，对于相邻两个三元组 (P, A, B) 和 (p, a, b) ，
满足 B >= b 。
根据 0 <= s[B] - s[b] <= B - b 又可以列出关于 x 的不等式。

联立所有不等式，不等式无解则没有合法方案。
否则随便选范围内一个 x 去算答案即可。
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

const int maxn = 200005, maxm = 2000005;
ll pos[2][maxn], ti[maxn];
int get[2][maxm];

struct Limit {
	ll p, a, b;
} li[maxn];

void solve(int o, int n, int m) {
	// for(int i = 1; i <= n; i ++)
		// debug(" %lld", pos[o][i]);
	// debug("\n");

	for(int i = 1; i <= n; i ++)
		li[i] = {pos[o][i], ti[i] / m, ti[i] % m};
	std::sort(li + 1, li + n + 1, [](Limit x, Limit y) {
				return x.b < y.b;
			});

	li[0] = {0, 0, 0};
	li[n + 1] = {0, -1, m};
	ll Lx = 0, Rx = 1000000000000000000;
	for(int i = 1; i <= n + 1; i ++) {
		if(i < n) {
			Lx = std::max(Lx, (li[i].p + li[i].a) / (li[i].a + 1));
			if(li[i].a)
				Rx = std::min(Rx, li[i].p / li[i].a);
		}

		ll dp = li[i].p - li[i - 1].p;
		ll da = li[i].a - li[i - 1].a;
		ll L = 0, R = li[i].b - li[i - 1].b;

		if(da < 0) {
			dp = - dp;
			da = - da;
			L = - R;
			R = 0;
		}

		if(da) {
			Lx = std::max(Lx, (dp - R + da - 1) / da);
			Rx = std::min(Rx, (dp - L) / da);
		} else if(dp < L or dp > R)
			puts("NO"), exit(0);
	}

	if(Lx > Rx)
		puts("NO"), exit(0);

	// debug("%lld <= x <= %lld\n", Lx, Rx);

	ll x = Lx;
	for(int i = 1; i <= n + 1; i ++) {
		ll dis = li[i].p - li[i - 1].p - (li[i].a - li[i - 1].a) * x;
		for(int j = li[i].b - dis + 1; j <= li[i].b; j ++)
			get[o][j] = 1;
	}
}

int main() {
	int n = read, m = read;
	for(int i = 1; i <= n; i ++) {
		ti[i] = read;
		ll x = read, y = read;
		pos[0][i] = x - y + ti[i];
		pos[1][i] = x + y + ti[i];
		if((pos[0][i] & 1) or (pos[1][i] & 1))
			puts("NO"), exit(0);
		pos[0][i] >>= 1;
		pos[1][i] >>= 1;
	}

	solve(0, n, m);
	solve(1, n, m);

	char s[5] = "LDUR";
	for(int i = 1; i <= m; i ++)
		putchar(s[get[1][i] << 1 | get[0][i]]);
	puts("");
}
