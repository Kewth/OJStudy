#if 0
2020.03.14

将数从大到小排序，排在一起。
每次删除操作可以看作删掉最左边一列，减一操作可以看作删掉底下一列。
那么问题转换在二维平面上有一条折线，从 (0, 0) 开始，每次可以 x + 1 或 y + 1 。
所有折线上的点都是必败态，求 (0, 0) 是必败态还是必胜态。
有一个性质就是，若 (x, y) 和 (x + 1, y + 1) 都不在折线上，它们胜负态相同。
那么从 (0, 0) 直接走到的最大的 (k, k) ，然后问题从折线转换为矩形，简单判断即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
} read;

const int maxn = 100005;
int a[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		a[i] = read;

	std::sort(a + 1, a + n + 1);
	std::reverse(a + 1, a + n + 1);

	int x = 0, y = 0;
	while(y < a[x + 1])
		++ x, ++ y;
	-- x, -- y;

	int dy = a[x + 1] - y;

	while(y < a[x + 1])
		++ x;

	int dx = x - y;

	if(dx & 1 and dy & 1) puts("Second");
	else puts("First");
}
