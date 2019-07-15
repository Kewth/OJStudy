#if 0
2019.07.14

考虑相邻的四个数 a, b, c, d ，
由 a^c=b, b^c=d 得 a^c^b^c=b^d ，即 a=d 。
因此每三个构成一个循环节。
若 n 是 3 的倍数，那么可以等分成三种数 a, b, c 满足 a^b=c 即可。
否则，必须满足所有数都是 0 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define NO return puts("No"), 0
#define YES return puts("Yes"), 0

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 100005;
int a[maxn], b[maxn];

int main() {
	int n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	std::sort(a + 1, a + n + 1);
	if(n % 3 == 0) {
		int p = 1;
		for(int i = 1; i <= n; i += 3)
			b[i] = a[p ++];
		if(a[p - 1] != b[1])
			NO;
		for(int i = 2; i <= n; i += 3)
			b[i] = a[p ++];
		if(a[p - 1] != b[2])
			NO;
		for(int i = 3; i <= n; i += 3)
			b[i] = a[p ++];
		if(a[p - 1] != b[3])
			NO;
		if((b[3] ^ b[1]) != b[2])
			NO;
		YES;
	} else {
		if(a[1] == a[n] and a[1] == 0)
			YES;
		else
			NO;
	}
}
