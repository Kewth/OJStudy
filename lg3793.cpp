#if 0
2019.10.10

随机数据下的期望 O(n) - O(1) RMQ 。
分块，设块大小为 b ，对于每个块维护前缀 max 和后缀 max ，块间维护 st 表。
那么对于询问区间，完整的块间用 st 表 O(1) 查，离散的块查前缀或后缀 max ，
当 l, r 在同一个块内时暴力跑，这种情况的概率是 b / n ，复杂度为 O(b) 。
总的期望复杂度 O(n + n / b log(n / b)) - O(1 + b^2 / n) 。
大众做法是取 b 为 log(n) （因为 lxl 这么讲的，所以一堆人想都不想就跟着写），
但事实上从上式中可以发现当 b 取 log(n) 到 sqrt(n) 都是可以做到 O(n) - O(1) 的，
而且实践中发现取 sqrt(n) 比 log(n) 块。
#endif
#include <cstdio>
#include <cmath>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

namespace GenHelper {
	unsigned z1, z2, z3, z4, b;
	unsigned rand_() {
		b = ((z1 << 6) ^ z1) >> 13;
		z1 = ((z1 & 4294967294U) << 18) ^ b;
		b = ((z2 << 2) ^ z2) >> 27;
		z2 = ((z2 & 4294967288U) << 2) ^ b;
		b = ((z3 << 13) ^ z3) >> 21;
		z3 = ((z3 & 4294967280U) << 7) ^ b;
		b = ((z4 << 3) ^ z4) >> 12;
		z4 = ((z4 & 4294967168U) << 13) ^ b;
		return (z1 ^ z2 ^ z3 ^ z4);
	}
}; // namespace GenHelper

void ssrand(unsigned x) {
    using namespace GenHelper;
    z1 = x;
    z2 = unsigned((~x) ^ 0x233333333U);
    z3 = unsigned(x ^ 0x1234598766U);
    z4 = (~x) + 51;
}

int read() {
    using namespace GenHelper;
    int A = rand_() & 32767;
    int B = rand_() & 32767;
    return A * 32768 + B;
}

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 20000005, minb = 4400, maxb = 4475;
int a[maxn + maxb];
int highbit[maxn + maxb];
int st[maxn / minb][maxb];
int pre[maxn / minb][maxb];
int suf[maxn / minb][maxb];

inline void chkmax(int &x, int y) {
	if(y > x) x = y;
}

int main() {
	int n = input(), q = input(), s = input();
	ssrand(unsigned(s));
	/* int b = int(log2(n)); */
	int b = int(sqrt(n));
	int B = (n - 1) / b;

	for(int i = 0; i < n; i ++) {
		a[i] = read();
		chkmax(st[i / b][0], a[i]);
	}

	/* for(int i = 0; i < n; i ++) */
	/* 	debug(" %d", a[i]); */
	/* debug("\n"); */

	for(int i = B; i >= 0; i --)
		for(int k = 1; i + (1 << k) - 1 <= B; k ++)
			st[i][k] = std::max(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);

	for(int i = 0; i <= B; i ++) {
		int be = i * b;
		pre[i][0] = a[be];
		for(int k = 1; k < b; k ++)
			pre[i][k] = std::max(pre[i][k - 1], a[be + k]);
		suf[i][b - 1] = a[be + b - 1];
		for(int k = b - 2; k >= 0; k --)
			suf[i][k] = std::max(suf[i][k + 1], a[be + k]);
	}

	for(int k = 0; (1 << k) <= n << 1; k ++)
		for(int i = 1 << k; i < (1 << (k + 1)); i ++) {
			if(i > n) break;
			highbit[i] = k;
		}

	/* for(int i = 0; i <= B; i ++) { */
	/* 	for(int k = 0; k < b; k ++) */
	/* 		debug(" %d", pre[i][k]); */
	/* 	debug(" <- pre\n"); */
	/* } */

	/* for(int i = 0; i <= B; i ++) { */
	/* 	for(int k = 0; k < b; k ++) */
	/* 		debug(" %d", suf[i][k]); */
	/* 	debug(" <- suf\n"); */
	/* } */

	unsigned long long ans = 0;
	while(q --) {
		int l = read() % n;
		int r = read() % n;
		if(l > r)
			std::swap(l, r);
		int L = l / b, R = r / b;

		int now = 0;
		if(L == R)
			for(int i = l; i <= r; i ++)
				chkmax(now, a[i]);
		else {
			chkmax(now, suf[L][l % b]);
			chkmax(now, pre[R][r % b]);
			int len = R - L - 1;
			int k = highbit[len];
			if(len) {
				chkmax(now, st[L + 1][k]);
				chkmax(now, st[R - (1 << k)][k]);
			}
		}

		/* debug("%d-%d : %d\n", l, r, now); */
		ans += unsigned(now);
	}

	printf("%llu\n", ans);
}
