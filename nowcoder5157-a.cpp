#if 0
2020.04.17

  两个传送门一定是由到终点远的传到到终点近的，进一步可以知道一个传送门一定就在终点，只需考
虑另一个。二分答案，然后对于每个不能直接走到终点的人都能求出一个传送门的位置区间，所有区间
的交非空就可行。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 100005;
int a[maxn];

bool check (int n, int k) {
	int L = - 1000000000, R = 1000000000;
	for (int i = 1; i <= n; i ++)
		if (a[i] < -k or a[i] > k) {
			L = std::max(L, a[i] - k);
			R = std::min(R, a[i] + k);
		}
	return L <= R;
}

int main () {
	int T = read;
	while (T --) {
		int n = read;
		for (int i = 1; i <= n; i ++) read(a[i]);
		int l = 0, r = 1000000000;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (check(n, mid)) r = mid;
			else l = mid + 1;
		}
		printf("%d\n", l);
	}
}
