#if 0
2019.10.01
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline int input() { int x; scanf("%d", &x); return x; }
inline lolong linput() { lolong x; scanf("%lld", &x); return x; }

int main() {
	lolong a[5];
	for(int i = 0; i < 5; i ++)
		a[i] = input();
	std::sort(a, a + 5);

	if(a[0] + a[1] + a[2] + a[3] <= a[4])
		printf("%lld\n", a[0] + a[1] + a[2] + a[3]);
	else
		printf("%lld\n", (a[0] + a[1] + a[2] + a[3] + a[4]) >> 1);
}
