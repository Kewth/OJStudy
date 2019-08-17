#if 0
2019.08.14

考虑求权值值 >= x 的区间数量，套个二分就能求出答案。
枚举左端点，那么可行的右端点是一段后缀，而且最小右端点是单调的，尺取即可。
另外 k 是 O(n^2) 的，要开 long long 。
#endif
#include <cstdio>
#include <unordered_map>
#define debug(...) // fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline lolong input() { lolong x; scanf("%lld", &x); return x; }

const int maxn = 100005;
int a[maxn];

lolong check(int x, int n) {
	std::unordered_map<int, int> map;
	lolong res = 0;
	int now = 0;
	debug("check %d\n", x);
	for(int l = 1, r = 0; l <= n; l ++) {
		while(r <= n and not now) {
			r ++;
			map[a[r]] ++;
			if(map[a[r]] == x)
				now ++;
		}
		debug("%d-%d:%d\n", l, r, now);
		res += n - r + 1;
		if(map[a[l]] == x)
			now --;
		map[a[l]] --;
	}
	return res;
}

int main() {
	int n = input();
	lolong k = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	int l = 1, r = n;
	while(l < r) {
		int mid = (l + r + 1) >> 1;
		if(check(mid, n) >= k)
			l = mid;
		else
			r = mid - 1;
	}
	printf("%d\n", l);
}
