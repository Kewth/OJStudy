#pragma GCC optimize(3)
#if 0
2020.03.14

垃圾 hdu 不知道 tm 判的什么东西。
数组越界你给判 TLE 我也就理解了，未定义行为嘛。
踩 assert 你给判 WA ？return 1 你给判 WA ？
离谱。

由于 Nim 积有着出色的性质，可以直接套在矩形并的线段树上。
算是板子题，具体做法略。
坑巨多，卡空间。
注意需要将区间离散化，而区间的离散化和点的离散化是有略微不同的。
#endif
#include <cstdio>
#include <algorithm>
#include <cassert>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

int f[30][30];
int g[4][256][4][256];
int forcenim(int x, int y) {
	int res = 0;
	for(int i = 0; i < 30; i ++)
		if(x >> i & 1)
			for(int j = 0; j < 30; j ++)
				if(y >> j & 1)
					res ^= f[i][j];
	return res;
}

int nim(int x, int y) {
	int res = 0;
	for(int i = 0; i < 32; i += 8)
		for(int j = 0; j < 32; j += 8)
			res ^= g[i >> 3][x >> i & 255][j >> 3][y >> j & 255];
	return res;
}

int F(int x, int y) {
	int res = 1;
	for(int k = 0; k < 6; k ++) {
		int v = 1 << (1 << k);
		if((x & y) >> k & 1)
			res = res * v ^ forcenim(res, (v >> 1));
		if((x xor y) >> k & 1)
			res = res * v;
	}
	return res;
}

const int maxn = 200005;
struct	Tree {
	int cover, sum;
} pool[maxn << 2];
#define self pool[now]
#define lt (now << 1)
#define rt (now << 1 | 1)
int pre[maxn];

void update(int now, int L, int R) {
	if(self.cover)
		self.sum = pre[R] ^ pre[L - 1];
	else if(L == R)
		self.sum = 0;
	else
		self.sum = pool[lt].sum ^ pool[rt].sum;
}

void modify(int now, int L, int R, int l, int r, int x) {
	if(r < L or l > R) return;
	if(l <= L and R <= r) return self.cover += x, update(now, L, R);
	int M = (L + R) >> 1;
	modify(lt, L, M, l, r, x);
	modify(rt, M + 1, R, l, r, x);
	update(now, L, R);
}

void clear(int now, int L, int R) {
	self = {0, 0};
	if(L == R) return;
	int M = (L + R) >> 1;
	clear(lt, L, M);
	clear(rt, M + 1, R);
}

int sum(int L, int R, int l, int r) {
	if(r < L or l > R) return 0;
	if(l <= L and R <= r) {
		int t = R - L + 1;
		return (L & -L) ^ (t >> 1);
	}
	int M = (L + R) >> 1;
	return sum(L, M, l, r) ^ sum(M + 1, R, l, r);
}

struct Operation {
	int l, r, t, o;
} op[maxn];
int tmp[maxn], tp;

int main() {
	for(int i = 0; i < 30; i ++)
		for(int j = 0; j < 30; j ++)
			f[i][j] = F(i, j);

	for(int i = 0; i < 32; i += 8)
		for(int j = 0; j < 32; j += 8)
			for(int x = 0; x < 256; x ++)
				for(int y = 0; y < 256; y ++)
					g[i >> 3][x][j >> 3][y] = forcenim(x << i, y << j);

	int T = read;
	while(T --) {
		read.operator int();
		int n = 0, m = read;
		for(int i = 1; i <= m; i ++) {
			int lx = read, ly = read;
			int rx = read, ry = read;
			op[i * 2 - 1] = {ly, ry, lx, 1};
			op[i * 2] = {ly, ry, rx + 1, -1};
			tmp[++ n] = ly - 1;
			tmp[++ n] = ry;
		}

		int lim = (1 << 30) - 1;

		std::sort(tmp + 1, tmp + n + 1);
		n = int(std::unique(tmp + 1, tmp + n + 1) - tmp - 1);
		for(int i = 1; i <= n; i ++)
			pre[i] = sum(0, lim, 0, tmp[i]);

		std::sort(op + 1, op + m * 2 + 1, [](Operation a, Operation b) {
					return a.t < b.t;
				});

		int sg = 0;
		for(int i = 1; i <= m * 2; i ++) {
			if(pool[1].sum and op[i].t > op[i - 1].t)
				sg ^= nim(pool[1].sum, sum(0, lim, op[i - 1].t, op[i].t - 1));
			int l = int(std::lower_bound(tmp + 1, tmp + n + 1, op[i].l - 1) - tmp) + 1;
			int r = int(std::lower_bound(tmp + 1, tmp + n + 1, op[i].r) - tmp);
			modify(1, 1, n, l, r, op[i].o);
		}

		clear(1, 1, n);

		if(sg) puts("Yong Chol");
		else puts("Brother");
	}
}
