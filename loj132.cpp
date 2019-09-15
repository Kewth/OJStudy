#if 0
2019.08.30

通过单点修区间查实现区间修区间查。
可以通过实现一个等价的问题“修改后缀查询前缀”来实现。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1000005;
lolong bit1[maxn], bit2[maxn];

void add(int p, int x) {
	for(int k = p; k < maxn; k += k & -k) {
		bit1[k] += x;
		bit2[k] += 1ll * x * (maxn - p);
	}
}

lolong sum(int p) {
	if(p == 0)
		return 0;
	lolong sum1 = 0, sum2 = 0;
	for(int k = p; k; k -= k & -k) {
		sum1 += bit1[k];
		sum2 += bit2[k];
	}
	return sum2 - sum1 * (maxn - p - 1);
}

int main() {
	int n = input(), q = input();
	for(int i = 1; i <= n; i ++) {
		int x = input();
		add(i, x);
		add(i + 1, - x);
	}
	while(q --) {
		if(input() == 1) {
			int l = input(), r = input(), x = input();
			add(l, x);
			add(r + 1, - x);
		} else {
			int l = input(), r = input();
			printf("%lld\n", sum(r) - sum(l - 1));
		}
	}
}
