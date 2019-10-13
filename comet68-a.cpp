#if 0
2019.10.01
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

int main() {
	int T = input();
	while(T --) {
		int a = input(), b = input(), c = input(), d = input();
		int ans = 5;
		if(a < 0 and c > 0)
			ans ++;
		if(a > 0 and c < 0)
			ans ++;
		if(b < 0 and d > 0)
			ans ++;
		if(b > 0 and d < 0)
			ans ++;
		if(ans == 7)
			ans ++;
		printf("%d\n", ans);
	}
}
