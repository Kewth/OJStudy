#if 0
2019.08.11

先考虑弱化版：只有全局加值以及全局最大前缀和。
对于前缀 i ，全局加了 x 后前缀和的值为 s[i] + i * x 。
这是一个直线的形式，投射到二维平面上，相当于要求对于 k 求所有直线在 x = k 的最大值。
李超树能干这事，但是这是直线，另外没有修改，事实上，维护一个凸包就可以了，对于询问二分即可。

那么区间呢？
用分块解决即可，每个操作区间中，完整的块相当于上述弱化版，零散的块直接暴力做即可。
#endif
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <climits>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005, maxb = 1000;
lolong lazy[maxb];
lolong val[maxb][maxb];
int ll[maxb][maxb], rr[maxb][maxb], id[maxb][maxb], sz[maxb];

void build(int x, int b) {
	int p = 0;
	for(int i = 0; i < b; i ++) {
		val[x][i] += 1ll * (i + 1) * lazy[x];
		while(p and
				1ll * (i + 1) * ll[x][p - 1] + val[x][i] >
				1ll * (id[x][p - 1] + 1) * ll[x][p - 1] + val[x][id[x][p - 1]])
			p --;
		if(not p) {
			ll[x][0] = - 2000000000;
		} else {
			lolong d = val[x][id[x][p - 1]] - val[x][i];
			int pos = d >= 0 ? d / (i - id[x][p - 1]) : (d - i + id[x][p - 1] + 1) / (i - id[x][p - 1]);
			assert(pos >= ll[x][p - 1]);
			rr[x][p - 1] = pos;
			ll[x][p] = pos + 1;
		}
		rr[x][p] = 2000000000;
		id[x][p] = i;
		p ++;
	}
	sz[x] = p;
	lazy[x] = 0;
}

lolong max(int x, int b) {
	int p = std::upper_bound(ll[x], ll[x] + sz[x], lazy[x]) - ll[x] - 1;
	// debug("max %d -> %d : %d, %d, %lld\n", x, p, id[x][p], lazy[x], val[x][id[x][p]]);
	return 1ll * (id[x][p] + 1) * lazy[x] + val[x][id[x][p]];
}

int main() {
	int n = input();
	int b = sqrt(n) + 1;
	debug("block %d\n", b);
	for(int i = 0, now = 0; i < n; i ++) {
		if(not (i % b))
			now = 0;
		now += input();
		val[i / b][i % b] = now;
	}
	for(int i = n; i / b == (n - 1) / b; i ++)
		val[i / b][i % b] = val[i / b][i % b - 1];
	for(int i = 0; i < b; i ++)
		build(i, b);
	int q = input();
	while(q --) {
		int typ = input(), l = input() - 1, r = input() - 1;
		if(typ == 0) {
			int v = input();
			if(l / b == r / b) {
				for(int i = l; i <= r; i ++)
					val[i / b][i % b] += v * (i - l + 1);
				for(int i = r + 1; i / b == l / b; i ++)
					val[i / b][i % b] += v * (r - l + 1);
				build(l / b, b);
			} else {
				for(int i = l; i / b == l / b; i ++)
					val[i / b][i % b] += v * (i - l + 1);
				build(l / b, b);
				for(int i = l / b + 1; i < r / b; i ++)
					lazy[i] += v;
				for(int i = r; i / b == r / b; i --)
					val[i / b][i % b] += v * (i % b + 1);
				for(int i = r + 1; i / b == r / b; i ++)
					val[i / b][i % b] += v * (r % b + 1);
				build(r / b, b);
			}
		} else if(typ == 1) {
			lolong ans = LLONG_MIN, now = 0;
			for(int i = 0; i < l / b; i ++)
				now += val[i][b - 1] + lazy[i] * b;
			if(l / b == r / b) {
				for(int i = l; i <= r; i ++)
					ans = std::max(ans, now + val[i / b][i % b] + lazy[i / b] * (i % b + 1));
			} else {
				for(int i = l; i / b == l / b; i ++)
					ans = std::max(ans, now + val[i / b][i % b] + lazy[i / b] * (i % b + 1));
				for(int i = l / b + 1; i < r / b; i ++) {
					now += val[i - 1][b - 1] + lazy[i - 1] * b;
					ans = std::max(ans, now + max(i, b));
				}
				now += val[r / b - 1][b - 1] + lazy[r / b - 1] * b;
				for(int i = r; i / b == r / b; i --)
					ans = std::max(ans, now + val[i / b][i % b] + lazy[i / b] * (i % b + 1));
			}
			printf("%lld\n", ans);
		}
#if 0
		for(int i = 0; i < b; i ++) {
			debug("block %d(%d~%d), lazy=%lld:\n", i, i * b, i * b + b - 1, lazy[i]);
			for(int j = 0; j < b; j ++)
				debug("%lld\n", val[i][j]);
			for(int j = 0; j < b; j ++) {
				debug("%d~%d:%d\n", ll[i][j], rr[i][j], id[i][j]);
				if(rr[i][j] == 1000000000) break;
			}
		}
#endif
	}
}
