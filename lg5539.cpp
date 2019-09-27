#if 0
2019.09.27

大力压位，手写 bitset 卡常。
然后发现其实很像分块。
然后发现真他妈毒瘤你比标程少压一位，多开一个数组都不行。

具体的，维护集合表示 S 所有数的整数倍，查询的时候就求连续三个 1 的数量。
将这些数分块状压来维护，对于 S 的每个值 x ，
分两种情况，如果 x 比压位的块小，计算循环节，弄块的大小次是一定循环的。
否则 x 比压位的块大，暴力修改。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef unsigned long long BIT;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1000000005, maxm = 22;
const int base = 64, b = 6;
/* const int base = 1 << 20, b = 20; */
BIT BITFUCK;
BIT bit[maxn >> b];
BIT tmp[base];

int count(BIT x) {
	int res = 0;
	while(x) {
		res ++;
		x &= ~(x & -x);
	}
	return res;
}

int main() {
	int n = input(), m = input();

	while(m --) {
		int x = input();
		if(x <= base) {
			for(int j = 0; j < base; j ++)
				tmp[j] = 0;
			for(int j = 0; j < (x << b); j += x)
				tmp[j >> b] |= 1ull << (j & (base - 1));
			for(int j = 0; j <= (n >> b); j ++)
				bit[j] |= tmp[j % x];
		}

		else
			for(int j = x; j <= n; j += x)
				bit[j >> b] |= 1ull << (j & (base - 1));
	}

	int ans = 0;
	bit[0] &= - 2ull;

	for(int i = 0; i <= (n >> b); i ++) {
		BIT A = i ? (bit[i] &
			 ((bit[i] << 1) | (bit[i - 1] >> (base - 1))) &
			 ((bit[i] << 2) | (bit[i - 1] >> (base - 2)))) :
			(bit[i] & (bit[i] << 1) & (bit[i] << 2));
		BIT B = ((i == n >> b) and n != base - 1) ?
			(1ull << ((n + 1) % base)) - 1 :
			 - 1ull;

		/* for(int k = 0; k < base; k ++) */
		/* 	debug("%d", bool(bit[i] >> k & 1)); */
		/* debug("\n"); */
		/* for(int k = 0; k < base; k ++) */
		/* 	debug("%d", bool((bit[i] << 1 | (bit[i - 1] >> (base - 1))) >> k & 1)); */
		/* debug("\n"); */
		/* for(int k = 0; k < base; k ++) */
		/* 	debug("%d", bool((bit[i] << 2 | (bit[i - 1] >> (base - 2))) >> k & 1)); */
		/* debug("\n"); */
		/* debug("\n"); */

		ans += count(A & B);
	}

	printf("%d\n", ans);
}
