#if 0
2019.08.30

线性基求第 k 大异或和。
插入后需要改造线性基，使得每个 a[i] 如果第 j 位为 1 就不存在 a[j] (j != i) 。
然后将询问的 k 按二进制扫一遍，k 的第 i 位对应 a 的第 i 个不为 0 的数。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxk = 52;
lolong a[maxk];
lolong b[maxk];
int n, size;

inline void add(lolong x) {
	for(int k = maxk - 1; k >= 0; k --)
		if(x >> k & 1) {
			if(not a[k]) {
				a[k] = x;
				return;
			} else
				x ^= a[k];
		}
}

inline lolong Kth(lolong K) {
	if(n != size)
		K --;

	if(K >= (1ll << size))
		return -1;

	lolong res = 0;

	for(int k = 0; k < maxk; k ++)
		if(K >> k & 1)
			res ^= b[k];

	return res;
}

int main() {
	n = input();
	for(int i = 1; i <= n; i ++)
		add(linput());

	for(int k = 0; k < maxk; k ++)
		for(int kk = 0; kk < k; kk ++)
			if(a[k] >> kk & 1)
				a[k] ^= a[kk];

	for(int k = 0; k < maxk; k ++)
		if(a[k])
			b[size ++] = a[k];
	/* for(int k = 0; k < maxk; k ++) */
	/* 	debug("%d\n", size[k]); */

	int q = input();
	while(q --)
		printf("%lld\n", Kth(linput()));
}
