#if 0
date

NULL
#endif
#include <cstdio>
#include <algorithm>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

lolong gcd(lolong a, lolong b) {
	if(not b) return a;
	return gcd(b, a % b);
}

int ans;
lolong now[10000], ansli[10000];
void dfs(int d, lolong x, lolong a, lolong b) {
	lolong g = gcd(a, b);
	a /= g;
	b /= g;
	if(d >= ans) return;
	if(a < 0 or b < 0) return;
	if(a == 1 and b >= x) {
		now[++ d] = b;
		// 漏了 not ansli[1] ，调了一年
		if(not ansli[1] or d + 1 < ans or now[d] < ansli[d]) {
			for(int i = 1; i <= d; i ++)
				ansli[i] = now[i];
			ans = d;
		}
		return;
	}
	if(d + 1 >= ans) return;
	for(lolong c = std::max(x, (b + a - 1) / a); (ans - d) * b >= a * c; c ++) {
		now[d + 1] = c;
		dfs(d + 1, c + 1, a * c - b, b * c);
	}
}

int main() {
	int a = input(), b = input();
	int maxd = 1;
	while(true) {
		debug("try %d\n", maxd);
		ans = maxd;
		ansli[1] = 0;
		dfs(0, 1, a, b);
		if(ansli[1]) break;
		maxd ++;
	}
	for(int i = 1; i <= ans; i ++)
		printf("%lld ", ansli[i]);
	puts("");
}
