#if 0
2019.08.27

根据 SG 定理，拆分后的 SG 值只与 k 奇偶性有关，分类讨论。

0)
那么如果存在奇数 x 使得 sg(x) = 0 ，那么大于 x 的偶数 SG 值一定大于 0 ，
那么大于 x 的奇数 SG 值一定为 0 。

1) k % 2 = 0
sg(3) = 0
大于 x 的偶数 y 的 SG 值只能是 1/2 ，为 2 当且仅当 SG(x / 2) = 1 。

2) k % 2 = 1
sg(5) = 0
大于 x 的偶数 y 的 SG 值只能是 1 。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 100005;

int SG(lolong x, int k) {
	if(k)
		switch(x) {
			case 0:	return 0;
			case 1: return 1;
			case 2: return 0;
			case 3: return 1;
			case 4: return 2;
			default: return (x & 1) ? 0 : (SG(x >> 1, k) == 1 ? 2 : 1);
		}
	else
		switch(x) {
			case 0: return 0;
			case 1: return 1;
			case 2: return 2;
			default: return ! (x & 1);
		}
}

int main() {
	int T = input();

	while(T --) {
		int n = input(), k = linput() & 1, sg = 0;
		for(int i = 1; i <= n; i ++)
			sg ^= SG(linput(), k);

		debug("%d\n", sg);

		if(sg)
			puts("Kevin");
		else
			puts("Nicky");
	}
}
