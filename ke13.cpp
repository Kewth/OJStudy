#if 0
2019.08.24

考虑拿二分图去覆盖原图，最优的覆盖方式是拿 n / 2 和 n - n / 2 个点的完全二分图覆盖。
之后剩下两个子问题，递归计算即可。
#endif
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;

inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 5000005;

std::unordered_map<lolong, int> map;

int f(lolong n) {
	if(map.count(n))
		return map[n];
	return f(n - (n >> 1)) + 1;
}

int main() {
	lolong n = input();
	map[1] = map[2] = 1;
	printf("%d\n", f(n));
}
