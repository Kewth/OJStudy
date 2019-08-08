#if 0
2019.08.08

先枚举位数，考虑每一位的贡献，不难发现每一位与对称位的差值对 D 有 9..90..0 的贡献。
而这个值大到比它更低的所有对称位的最大贡献的和要高。
那么这个差值只可能是两个值，乘上贡献分别小于/大于当前的 D 。
枚举这两种值即可，总复杂度 O(2L * 2^L) 。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

lolong dfs(lolong a, lolong b, lolong d) {
	if(not a) return d == 0 ? 10 : 0;
	if(d < 0) d = - d;
	lolong c = a * b;
	int x = d / c;
	int max = b == 1 ? 9 : 10;
	if(a == 9)
		return x * c == d ? std::max(max - x, 0) : 0;
	lolong res = std::max(max - x, 0) * dfs(a / 100, b * 10, d - x * c);
	x ++;
	res += std::max(max - x, 0) * dfs(a / 100, b * 10, d - x * c);
	debug("%lld, %lld, %lld: %lld\n", a, b, d, res);
	return res;
}

int main() {
	lolong ans = 0, d = input();
	for(lolong a = 999999999999999999; a; a /= 10)
		ans += dfs(a, 1, d);
	printf("%lld\n", ans);
}
