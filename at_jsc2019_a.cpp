#if 0
2019.08.24
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

int main() {
	int m = input(), d = input(), tot = 0;
	for(int i = 4; i <= m; i ++)
		for(int x = 2; x <= i and x < 10; x ++)
			if(not (i % x) and 2 <= i / x and i / x < 10 and x * 10 + i / x <= d)
				tot ++;
	printf("%d\n", tot);
}
