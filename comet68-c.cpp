#if 0
2019.10.01
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 200005;
int l1[maxn], r1[maxn];
int l2[maxn], r2[maxn];

int main() {
	int n = input(), m = input();

	for(int i = 1; i <= n; i ++) {
		l1[i] = input();
		r1[i] = input();
	}

	for(int i = 1; i <= m; i ++) {
		l2[i] = input();
		r2[i] = input();
	}

	lolong ans = 0;

	int p = 1;
	for(int i = 1; i <= n; i ++) {
		while(p <= m and r2[p] < l1[i])
			p ++;
		if(p > m)
			break;
		int tmp = p;
		while(tmp <= m and l2[tmp] <= r1[i])
			tmp ++;
		ans += tmp - p;
		p = std::max(1, tmp - 2);
	}

	printf("%lld\n", ans);
}
