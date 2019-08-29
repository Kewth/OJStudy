#if 0
2019.08.28

分块 + 懒标记
#endif
#include <cstdio>
#include <cmath>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100500, maxb = 333, mod = 10007;
int s[maxb][maxb];
int lazymul[maxb], lazyadd[maxb];

int b;

void push(int p) {
	for(int i = 0; i < b; i ++)
		((s[p][i] *= lazymul[p]) += lazyadd[p]) %= mod;
	lazymul[p] = 1;
	lazyadd[p] = 0;
}

void add_one(int l, int r, int c) {
	push(l / b);
	for(int i = l; i <= r; i ++)
		(s[i / b][i % b] += c) %= mod;
}

void add_all(int l, int r, int c) {
	for(int i = l; i <= r; i ++)
		(lazyadd[i] += c) %= mod;
}

void mul_one(int l, int r, int c) {
	push(l / b);
	for(int i = l; i <= r; i ++)
		(s[i / b][i % b] *= c) %= mod;
}

void mul_all(int l, int r, int c) {
	for(int i = l; i <= r; i ++) {
		(lazymul[i] *= c) %= mod;
		(lazyadd[i] *= c) %= mod;
	}
}

int main() {
	int n = input(), q = n;

	b = int(sqrt(n) + 1);

	for(int i = 0; i < n; i ++)
		s[i / b][i % b] = input();

	for(int i = 0; i < b; i ++)
		lazymul[i] = 1;

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
		}

		else if(typ == 1) {
			if(l / b == r / b)
				mul_one(l, r, c);
			else {
				mul_one(l, l / b * b + b - 1, c);
				mul_all(l / b + 1, r / b - 1, c);
				mul_one(r / b * b, r, c);
			}
		}

		else
			printf("%d\n", (s[r / b][r % b] * lazymul[r / b] + lazyadd[r / b]) % mod);

		/* for(int i = 0; i < n; i ++) */
		/* 	debug(" %d", (s[i / b][i % b] * lazymul[i / b] + lazyadd[i / b]) % mod); */
		/* debug("\n"); */
	}
}
