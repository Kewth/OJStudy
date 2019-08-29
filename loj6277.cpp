#if 0
2019.08.28

分块 + 懒标记
#endif
#include <cstdio>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 50200, maxb = 233;
int s[maxb][maxb];
int lazy[maxb];

int b;

void add_one(int l, int r, int c) {
	for(int i = l; i <= r; i ++)
		s[i / b][i % b] += c;
}

void add_all(int l, int r, int c) {
	for(int i = l; i <= r; i ++)
		lazy[i] += c;
}

int main() {
	int n = input(), q = n;

	b = int(sqrt(n) + 1);

	for(int i = 0; i < n; i ++)
		s[i / b][i % b] = input();

	while(q --) {
		int typ = input(), l = input() - 1, r = input() - 1, c = input();
		if(typ == 0) {
			if(l / b == r / b)
				add_one(l, r, c);
			else {
				add_one(l, l / b * b + b - 1, c);
				add_all(l / b + 1, r / b - 1, c);
				add_one(r / b * b, r, c);
			}
		} else
			printf("%d\n", s[r / b][r % b] + lazy[r / b]);
	}
}
