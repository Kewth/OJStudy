#if 0
2019.09.15
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1000005, maxb = 12;
lolong f[maxb][maxn];
int s[100];

int main() {
	for(int b = 2; b <= 10; b ++) {
		int now = 0;
		for(int i = 1; i < maxn; i ++) {
			s[0] ++;
			now ++;
			for(int j = 0; s[j] == b; j ++) {
				s[j] = 0;
				now -= b;
				s[j + 1] ++;
				now ++;
			}
			f[b][i] = f[b][i - 1] + now;
		}
		for(int j = 0; j < 100; j ++)
			s[j] = 0;
	}

	int T = input();
	for(int i = 1; i <= T; i ++) {
		int n = input(), b = input();
		printf("Case #%d: %lld\n", i, f[b][n]);
	}
}
