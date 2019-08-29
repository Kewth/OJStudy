#if 0
2019.08.28

分块 + 懒标记 + 暴力。
对于没被标记的块，即使它是完整的，照样暴力算，这样复杂度是有保障的。
因为每个被暴力算的完整块之后都会被标记，每次操作最多只有两个块被暴力算且没有标记。
#endif
#include <cstdio>
#include <cmath>
#include <map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100500, maxb = 333;
int s[maxb][maxb];
int lazy[maxb];

int b, ans;

void push(int p) {
	if(not lazy[p])
		return;
	for(int i = 0; i < b; i ++)
		s[p][i] = lazy[p];
	lazy[p] = 0;
}

void modify_one(int l, int r, int c) {
	push(l / b);
	for(int i = l; i <= r; i ++) {
		int &now = s[i / b][i % b];
		if(now == c)
			ans ++;
		now = c;
	}
}

void modify_all(int l, int r, int c) {
	for(int i = l; i <= r; i ++) {
		if(lazy[i])
			ans += lazy[i] == c ? b : 0;
		else
			modify_one(i * b, i * b + b - 1, c);
		lazy[i] = c;
	}
}

int main() {
	int n = input(), q = n;

	b = int(sqrt(n) + 1);

	for(int i = 0; i < n; i ++)
		s[i / b][i % b] = input();

	while(q --) {
		int l = input() - 1, r = input() - 1, c = input();

		ans = 0;

		if(l / b == r / b)
			modify_one(l, r, c);

		else {
			modify_one(l, l / b * b + b - 1, c);
			modify_all(l / b + 1, r / b - 1, c);
			modify_one(r / b * b, r, c);
		}

		printf("%d\n", ans);

		/* for(int i = 0; i < n; i ++) */
		/* 	debug(" %d", (s[i / b][i % b] * lazymul[i / b] + lazymodify[i / b]) % mod); */
		/* debug("\n"); */
	}
}
