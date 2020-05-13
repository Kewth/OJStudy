#if 0
2020.05.13

  如果确定了去掉的点，贪心，两边排序匹配即可。
  而每个点都可以去掉的话，还是先排序，处理个前缀奇怪度最大值和后缀奇怪度最大值即可。
#endif
#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 200005;
par a[maxn];
int b[maxn], c[maxn];
int pre[maxn], suf[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n + 1; i ++) a[i] = par(read, i);
	for (int i = 1; i <= n; i ++) read(b[i]);
	std::sort(a + 1, a + n + 2);
	std::sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i ++)
		pre[i] = std::max(pre[i - 1], a[i].first - b[i]);
	for (int i = n + 1; i > 1; i --)
		suf[i] = std::max(suf[i + 1], a[i].first - b[i - 1]);
	for (int i = 1; i <= n + 1; i ++)
		c[a[i].second] = std::max(pre[i - 1], suf[i + 1]);
	for (int i = 1; i <= n + 1; i ++)
		printf("%d ", c[i]);
	puts("");
}
