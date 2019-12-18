#if 0
2019.12.17

假设一共有 x 种颜色，那么合法 a 的值不是 x - 1 就是 x ，
其中若 a[i] = x - 1 说明 i 的颜色是唯一的，否则说明存在另一个点与之颜色相同。
设有 k 个点满足 a[i] = x - 1 ，其他 n - k 个点满足 a[i] = x ，
那么去掉这 k 个点的影响，a 合法当且仅当能将 n - k 个点分配 x - k 种颜色，
满足每个颜色都有至少两个点，这是很好 O(1) 判断的。
需要特判的是颜色两两不同，也就是 k = n 的情况。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
	template<class T, class ...A> inline void operator () (T &x, A &...a)
	{ x = *this; this -> operator ()(a...); }
} read;

const int maxn = 100005;
int a[maxn];

inline bool check(int n, int m) {
	return 1 <= m and m <= n / 2;
}

int main() {
	int n = read, max = 0;

	for(int i = 1; i <= n; i ++)
		max = std::max(max, a[i] = read);

	int tot = 0;
	for(int i = 1; i <= n; i ++)
		if(a[i] == max - 1)
			++ tot;
		else if(a[i] < max - 1)
			return puts("No"), 0;

	if(tot == 0 and max == n - 1)
		return puts("Yes"), 0;

	if(check(n - tot, max - tot)) puts("Yes");
	else puts("No");
}
