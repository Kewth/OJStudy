/*
 * Since g++10 is released, some characters is not valid inside #if 0 :(
 * So, why not using clang++? :D

 * Date:
  2020.06.02

 * Solution:
  对于一个子串有 a 个 1 和 b 个 0 ，该子串合法当且仅当 a 为偶数或者 b >= 2 且 a 不为 1 。
那么对于一个询问可以分治，记录子区间最左边最右边两个 0 两个 1 的位置即可更新答案，用线段
树动态维护这个分治即可。

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
#include <algorithm>
#include <vector>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 1000005;
struct Data {
	int len;
	int l1, l2, r1, r2;
	int L1, L2, R1, R2;
	int place_holder;
	ll val;
} seg[maxn << 2];
#define ls (now << 1)
#define rs (now << 1 | 1)

void getmin (std::vector<int> a, int &x, int &y) {
	std::sort(a.begin(), a.end());
	x = a[0];
	y = a[1];
}

ll shit (int n, int m) {
	/* debug("%d %d -> %lld\n", */
	/* 		n, m, 1ll * (n >> 1) * (m >> 1) + 1ll * ((n + 1) >> 1) * ((m + 1) >> 1)); */
	return 1ll * (n >> 1) * (m >> 1) + 1ll * ((n + 1) >> 1) * ((m + 1) >> 1);
}

ll fuck (int n, int m) {
	return 1ll * n * m + std::max(n - 1, 0) + std::max(m - 1, 0);
}

inline Data operator + (Data a, Data b) {
	Data c;
	c.len = a.len + b.len;
	getmin({a.l1 == a.len ? c.len : a.l1, a.l2 == a.len ? c.len : a.l2,
			a.len + b.l1, a.len + b.l2}, c.l1, c.l2);
	getmin({b.r1 == b.len ? c.len : b.r1, b.r2 == b.len ? c.len : b.r2,
			b.len + a.r1, b.len + a.r2}, c.r1, c.r2);
	getmin({a.L1 == a.len ? c.len : a.L1, a.L2 == a.len ? c.len : a.L2,
			a.len + b.L1, a.len + b.L2}, c.L1, c.L2);
	getmin({b.R1 == b.len ? c.len : b.R1, b.R2 == b.len ? c.len : b.R2,
			b.len + a.R1, b.len + a.R2}, c.R1, c.R2);
	c.val = a.val + b.val;

	c.val += 1ll * (a.len - a.r1) * (b.len - b.l1);
	c.val += 1ll * (a.len - a.r2) * b.l1;
	c.val += 1ll * (b.len - b.l2) * a.r1;

	c.val += shit(a.r2 - 1, b.l1) + (a.r1 & 1 ? (b.l1 + 1) >> 1 : b.l1 >> 1);
	c.val += shit(a.r1, b.l2 - 1) + (b.l1 & 1 ? (a.r1 + 1) >> 1 : a.r1 >> 1);
	c.val -= shit(a.r1, b.l1);

	if (a.R1 < a.len)
		c.val += fuck(a.R2 - a.R1 - 1, a.R1) - fuck(a.R2 - a.R1 - 1, a.R1 + b.L1);
	if (b.L1 < b.len)
		c.val += fuck(b.L2 - b.L1 - 1, b.L1) - fuck(b.L2 - b.L1 - 1, b.L1 + a.R1);

	/* debug("%d : %lld (%lld %lld)\n", c.len, c.val, a.val, b.val); */

	return c;
}

void build (int now, int L, int R) {
	if (L == R) {
		seg[now].len = 1;
		seg[now].l2 = seg[now].r2 = 1;
		seg[now].L2 = seg[now].R2 = 1;
		int x = read;
		seg[now].l1 = seg[now].r1 = x;
		seg[now].L1 = seg[now].R1 = x ^ 1;
		seg[now].val = x ^ 1;
		return;
	}
	int M = (L + R) >> 1;
	build(ls, L, M);
	build(rs, M + 1, R);
	seg[now] = seg[ls] + seg[rs];
}

void modify (int now, int L, int R, int p) {
	if (L == R) {
		seg[now].l1 ^= 1;
		seg[now].r1 ^= 1;
		seg[now].L1 ^= 1;
		seg[now].R1 ^= 1;
		seg[now].val ^= 1;
		return;
	}
	int M = (L + R) >> 1;
	if (p <= M) modify(ls, L, M, p);
	else modify(rs, M + 1, R, p);
	seg[now] = seg[ls] + seg[rs];
}

Data query (int now, int L, int R, int l, int r) {
	if (l <= L and R <= r) return seg[now];
	int M = (L + R) >> 1;
	if (l <= M and r > M) return query(ls, L, M, l, r) + query(rs, M + 1, R, l, r);
	return l <= M ? query(ls, L, M, l, r) : query(rs, M + 1, R, l, r);
}

int main () {
	int n = read;
	build(1, 1, n);
	int q = read;
	while (q --) {
		int o = read;
		if (o == 1) modify(1, 1, n, read);
		if (o == 2) {
			int l = read, r = read;
			Data d = query(1, 1, n, l, r);
			printf("%lld\n", d.val);
		}
	}
}
