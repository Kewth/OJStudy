#if 0
2020.02.05

狄利克雷前缀和。
把每个质数看作一个维度，一个数看作一个点，
点上某个维度的值是数质因数分解的结果。
那么 a[i] 能贡献到 b[j] 当且仅当 i 的每一维都不超过 j ，
这就是个高维前缀和，复杂度 O(nloglogn) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef unsigned int uint;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator uint () { uint x; return scanf("%u", &x), x; }
} read;

uint seed;
inline uint getnext(){
	seed^=seed<<13;
	seed^=seed>>17;
	seed^=seed<<5;
	return seed;
}

const int maxn = 20000005;
uint a[maxn];
bool nop[maxn];

int main() {
	int n = read;
	seed = read;
	for(int i = 1; i <= n; i ++)
		a[i] = getnext();

	for(int i = 2; i <= n; i ++)
		if(!nop[i]) {
			if(i <= n / i)
				for(int j = i * i; j <= n; j += i)
					nop[j] = 1;
			for(int j = i; j <= n; j += i)
				a[j] += a[j / i];
		}

	uint ans = 0;
	for(int i = 1; i <= n; i ++)
		ans ^= a[i];
	printf("%u\n", ans);
}
