#if 0
2020.04.03

将操作分为两部分，前一部分第 i 个操作的左端点设为 i ，可以保证每个操作都染到点，
后一部分每个操作左端点是上个操作的右端点 +1 ，可以保证每个点被染到。
枚举这个分界线即可。
#endif
#include <cstdio>
#include <algorithm>
#include <functional>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;
struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
} read;

const int maxn = 100005;
int a[maxn];
int ans[maxn];
ll suf[maxn];
int pre[maxn];

int main() {
	int n = read, m = read;
	for (int i = 1; i <= m; i ++)
		a[i] = read;
	for (int i = m; i; i --)
		suf[i] = suf[i + 1] + a[i];

	for (int i = 1; i <= m; i ++)
		pre[i] = std::max(pre[i - 1], i + a[i] - 1);

	if (pre[m] > n)
		return puts("-1"), 0;

	for (int i = 0; i <= m; i ++)
		if (i < n - suf[i + 1] + 1 and n - suf[i + 1] + 1 <= pre[i] + 1) {
			for (int j = 1; j <= i; j ++)
				printf("%d ", j);
			for (int j = i + 1; j <= m; j ++)
				printf("%lld ", n - suf[j] + 1);
			puts("");
			return 0;
		}

	puts("-1");
}
