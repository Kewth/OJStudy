#if 0
2019.09.01
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

int main() {
	int n = input();
	printf("%lld\n", 1ll * n * (n - 1) >> 1);
}
