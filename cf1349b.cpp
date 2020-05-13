#if 0
2020.05.12

  JBT
  首先必须存在一个 k 。然后如果存在相邻两个数 >= k 就一定可行，一直选三个数进行操作即可。
  把相邻这个条件推广，可以发现只要存在一个长度大于 1 的区间的中位数 >= k ，那么在这个区间
操作后就会产生相邻的 >= k 的数。如果不存在该区间，那么任意选一个区间操作都不会使 >= k 的
数增加。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
int a[maxn];

int main () {
	int T = read;
	while (T --) {
		int n = read, k = read, tot = 0;
		for (int i = 1; i <= n; i ++)
			tot += (a[i] = read) == k;

		if (!tot) {
			puts("no");
			goto shit;
		}

		if (n == 1) {
			puts("yes");
			goto shit;
		}

		a[n + 1] = a[n + 2] = -1;
		for (int i = 1; i <= n; i ++)
			if (a[i] >= k and (a[i + 1] >= k or a[i + 2] >= k)) {
				puts("yes");
				goto shit;
			}

		puts("no");
shit:;
	}
}
