#if 0
2019.08.17

由于所有数是正数，操作后的数一定比相邻两个数大。
考虑倒推，那么比相邻两个数大的一定比相邻两个数后做操作，
每次对这样的数减去相邻两个数即可。
#endif
#include <cstdio>
#include <queue>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long lolong;
inline int input() { int x; scanf("%d", &x); return x; }

const int maxn = 200005;
int a[maxn], b[maxn];

int n;
inline int &B(int x) {
	if(x < 1) return b[x + n];
	if(x > n) return b[x - n];
	return b[x];
}

int main() {
	n = input();
	for(int i = 1; i <= n; i ++)
		a[i] = input();
	std::queue<int> q;
	for(int i = 1; i <= n; i ++) {
		b[i] = input();
		if(b[i] > B(i - 1) and b[i] > B(i + 1))
			q.push(i);
	}
	lolong ans = 0;
	while(not q.empty()) {
		int p = q.front();
		q.pop();
		int sum = B(p - 1) + B(p + 1);
		int max = std::max(a[p], std::max(B(p - 1), B(p + 1)));
		int times = (b[p] - max + sum - 1) / sum;
		b[p] -= times * sum;
		ans += times;
		// debug("%d: %d\n", p, b[p]);
		if(b[p] < a[p]) {
			puts("-1");
			return 0;
		}
		if(B(p - 1) > B(p - 2) and B(p - 1) > b[p])
			q.push(p == 1 ? n : p - 1);
		if(B(p + 1) > B(p + 2) and B(p + 1) > b[p])
			q.push(p == n ? 1 : p + 1);
	}
	for(int i = 1; i <= n; i ++)
		if(b[i] != a[i]) {
			puts("-1");
			return 0;
		}
	printf("%lld\n", ans);
}
