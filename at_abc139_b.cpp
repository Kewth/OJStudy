#if 0
2019.09.01
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

int main() {
	int a = input() - 1, b = input() - 1;
	printf("%d\n", (b + a - 1) / a);
}
