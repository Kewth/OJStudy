#if 0
2019.09.26

考虑倒推，从最后的值 x 开始，每次将一个数拆成 m 个，
如果最后能凑出一个数列每一项都比原数列大，那么 x 就是可行的。
而这里的“可行的”具有可二分性。

贪心，如果当前数列的最大值可以拆就拆，除非拆掉后的最大值会比原数列未匹配的最大值小，
此时最大值不能拆，考虑与原数列的最大值匹配，
直接匹配是不行的，事实上最优的方案是将不比数列未匹配最大值小的最大值匹配上。

综上，将原数列排序后用 set 维护构造的数列即可。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 50005;
int a[maxn], b[maxn];
int n, m;

bool check(int x) {
	/* debug("check %d\n", x); */
	std::multiset<int> set;
	set.insert(x);
	int now = n;
	int t = (n - 1) / (m - 1);
	while(t --) {
		if(set.empty())
			return 0;
		std::multiset<int>::iterator it = -- set.end();
		if(*it < a[now])
			return 0;
		while(*it - b[1] < a[now]) {
			set.erase(set.lower_bound(a[now --]));
			if(set.empty())
				return 0;
			it = -- set.end();
			if(*it < a[now])
				return 0;
		}
		x = *it;
		set.erase(it);
		for(int i = 1; i <= m; i ++)
			set.insert(x - b[i]);
		/* for(int k : set) */
		/* 	debug(" %d", k); */
		/* debug("\n"); */
	}
	int p = 0;
	for(int k : set)
		if(k < a[++ p])
			return 0;
	return 1;
}

int main() {
	n = input(), m = input();

	for(int i = 1; i <= n; i ++)
		a[i] = input();
	for(int i = 1; i <= m; i ++)
		b[i] = input();

	std::sort(a + 1, a + n + 1);
	std::sort(b + 1, b + m + 1);

	int l = 1, r = 1000000000;
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid))
			r = mid;
		else
			l = mid + 1;
	}

	printf("%d\n", l);
}
