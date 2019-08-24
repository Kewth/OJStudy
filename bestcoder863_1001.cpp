#if 0
2019.08.24
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

int main() {
	int T = input();

	while(T --) {
		int n = input();
		printf("%d\n", n ^ 1);
	}
}
