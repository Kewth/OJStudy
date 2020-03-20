#if 0
2020.03.15

构造，前面放 1 到 k ，令 k 尽可能大，
然后第 k + 1 个数看着办，后面全填不造成影响的 inf 。
m = 0 需要特判。
#endif
#include <cstdio>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

int main() {
	int n = read, m = read;

	if(m == 0) {
		for(int i = 1; i <= n; i ++)
			printf("%d ", 999995000 + i);
		puts("");
		return 0;
	}

	int max = 0, now = 0;
	while(now + (max >> 1) < m) {
		now += max >> 1;
		++ max;
	}

	if(max >= n) return puts("-1"), 0;

	int d = 1;
	while(now + ((max - d + 1) >> 1) > m)
		++ d;

	now += (max - d + 1) >> 1;
	if(now != m or d > max) return puts("-1"), 0;

	for(int i = 1; i <= max; i ++)
		printf("%d ", i);
	printf("%d ", max + d);
	for(int i = max + 2; i <= n; i ++)
		printf("%d ", 900000000 + i * 10000);
	puts("");
}
