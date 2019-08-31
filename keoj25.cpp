#if 0
2019.08.31

二维差分套上一维差分。
然而又 TLE 又 MLE （我擦真的毒瘤）。
只用二维差分代替掉一维差分，不难发现总存在两个等差数列作差成指定常数数列。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 10000005;
lolong a[maxn];

int main() {
	int n = input(), q = input();

	while(q --) {
		if(input() == 1) {
			int p = input();
			lolong x = linput();
			a[p] += x;
			a[p + 1] -= x << 1;
			a[p + 2] += x;
		}

		else {
			int l = input(), r = input();
			lolong x = linput(), y = linput();
			if(l == r) {
				a[l] += x;
				a[l + 1] -= x << 1;
				a[l + 2] += x;
			} else {
				lolong d = (y - x) / (r - l);
				a[l] += x;
				a[l + 1] -= x - d;
				a[r + 1] -= y + d;
				a[r + 2] += y;
			}
		}
	}

	lolong max = 0, xor_sum = 0;

	for(int i = 1; i <= n; i ++)
		a[i] += a[i - 1];
	for(int i = 1; i <= n; i ++) {
		a[i] += a[i - 1];
		max = std::max(max, a[i]);
		xor_sum ^= a[i];
	}

	printf("%lld %lld\n", max, xor_sum);
}
