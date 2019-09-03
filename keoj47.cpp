#if 0
2019.09.03

消逆序对排序。
每次操作找到区间内所有相邻逆序对并交换，直到区间内没有逆序对为止。
很像冒泡，同样可以知道总交换次数是 O(n^2) 的。
如果能够快速找到区间内的逆序对位置，就有可能解决本问题。

用 set 记录所有相邻逆序对的左端点。
每次操作 lower_bound 到区间内的左端点 i ，并与 i + 1 交换，
然后若产生新的逆序对就继续加入 set 。
复杂度 O(n^2 logn + q logn) 。
#endif
#include <cstdio>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 1010;
int a[maxn];

int main() {
	int n = input();

	for(int i = 1; i <= n; i ++)
		a[i] = input();

	lolong sum = 0;

	for(int i = 1; i <= n; i ++)
		sum += 1ll * a[i] * i;

	int q = input();

	std::set<int> st;
	for(int i = 1; i < n; i ++)
		if(a[i] > a[i + 1])
			st.insert(i);
	st.insert(n + 1);

	while(q --) {
		int l = input(), r = input(), x;
		while((x = *st.lower_bound(l)) < r) {
			st.erase(x);

			sum -= 1ll * a[x] * x;
			sum -= 1ll * a[x + 1] * (x + 1);
			std::swap(a[x], a[x + 1]);
			sum += 1ll * a[x] * x;
			sum += 1ll * a[x + 1] * (x + 1);

			if(x + 2 <= n and a[x + 1] > a[x + 2])
				st.insert(x + 1);
			else
				st.erase(x + 1);

			if(x - 1 >= 1 and a[x - 1] > a[x])
				st.insert(x - 1);
			else
				st.erase(x - 1);
		}

		/* for(int i = 1; i <= n; i ++) */
		/* 	debug(" %d", a[i]); */
		/* debug("\n"); */

		printf("%lld\n", sum);
	}
}
