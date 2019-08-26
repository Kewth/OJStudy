#if 0
2019.08.26

斯特灵公式模板，直接用 log10 计算位数，
有些小 tricks ，例如把 log(a ^ b) 写成 log(a) * b ，把 log(a + b) 写成 log(a) * log(b) 。
#endif
#include <cstdio>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

#ifndef M_E
double M_E = exp(1);
#endif

int main() {
	int T = input();
	while(T --) {
		int n = input();
		switch(n) {
			case 0: case 1: case 2: case 3: puts("1"); break;
			case 4: puts("2"); break;
			case 5: case 6: puts("3"); break;
			default: printf("%lld\n",
							 lolong(log10(n * M_E * 2) * 0.5 + log10(n / M_E) * n + 1));
		}
		debug("%lf\n", log10(n * M_E * 2) * 0.5 + log10(n / M_E) * n);
	}
}
