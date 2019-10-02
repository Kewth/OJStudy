#if 0
2019.10.02

先将 py 之间建完全图，考虑删掉最少的边。
分 n 奇偶性讨论即可。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

int main() {
	int q = input();
	while(q --) {
		int n = input(), k = input();

		if(k > n or k & 1) {
			puts("renrendoushijwj");
			continue;
		}

		lolong ans = 1ll * n * (n - 1) >> 1;
		if(n & 1)
			printf("%lld\n", ans - (k >> 1));
		else
			printf("%lld\n", ans - ((n - k) >> 1));
	}
}
