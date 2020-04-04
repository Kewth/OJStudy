#if 0
2020.02.25

贪心，每当有两个 a 相同的元素时，选择 t 较小的元素，令它的 a = a + 1 。
但直接这样做是 O(n^2) 的。
将元素按初始的 a 排序，维护一段 t 不增的元素：
每次加入 a 最小的未加入的元素，如果它在当前的段中，由于 t 是不增的，
可以二分出这个元素的位置，并将后面的一段整体右移。
然后将当前段中小于 a 的位置的元素删掉。
直接用 set 按值域维护这段元素即可。
#endif
#include <cstdio>
#include <algorithm>
#include <set>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	inline operator ll () { ll x; return scanf("%lld", &x), x; }
	inline operator char () { char x[3]; return scanf("%s", x), *x; }
} read;

const int maxn = 200005;
struct Cate {
	int a, t;
} ca[maxn];

int main() {
	int n = read;
	for(int i = 1; i <= n; i ++)
		ca[i].a = read;
	for(int i = 1; i <= n; i ++)
		ca[i].t = read;

	std::sort(ca + 1, ca + n + 1, [](Cate a, Cate b) {
				return a.a < b.a;
			});

	std::multiset<int> s;
	int l = 1, r = 0;
	ll sum = 0, ans = 0;
	ca[n + 1] = {2000000000, 0};
	for(int i = 1; i <= n + 1; i ++) {
		while(l <= r and l < ca[i].a) {
			auto it = -- s.end();
			sum -= *it;
			ans += sum;
			++ l;
			s.erase(it);
		}
		if(l > r)
			l = r = ca[i].a;
		else
			++ r;
		sum += ca[i].t;
		s.insert(ca[i].t);
	}

	printf("%lld\n", ans);
}
