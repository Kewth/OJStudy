/*
 * Author: Kewth

 * Date:
  2020.11.14

 * Solution:
 * 挖掘性质

  称一个机器是安全的，当且仅当对应的 A > B ，我们可以发现两个关键性质：

  1. 安全的机器的球一定不会被替换，因为这种替换的唯一意义是去吃掉不安全的机器，而直接
把不安全机器自己的球替换掉吃自己一定不会更劣。

  2. 不安全的机器除了被吃掉外，还可以通过替换变为安全机器，而至多只有一个不安全机器有
这个归宿，因为一个不安全机器都通过替换成为安全机器后可以吃掉所有 A 比它小的不安全机器。

  那么做法就很简单了，枚举通过替换变为安全机器的不安全机器，只需要预处理比它大的不安全
机器中有多少是不能被吃掉的即可。

 * Digression:

 * CopyRight:
   __  __                  __   __
  |  |/  |.-----.--.--.--.|  |_|  |--.
  |     < |  -__|  |  |  ||   _|     |
  |__|\__||_____|________||____|__|__|

 */

#include <cstdio>
#include <algorithm>
#define debug(...) fprintf(stderr, __VA_ARGS__)

typedef long long ll;
typedef std::pair<int, int> par;

static struct {
	inline operator int () { int x; return scanf("%d", &x), x; }
	template<class T> inline void operator () (T &x) { x = *this; }
} read;

const int maxn = 200005;
int a[maxn], b[maxn];
par pr[maxn << 1];
int st[maxn];
int suf[maxn];

int main () {
	int n = read;
	for (int i = 1; i <= n; i ++) read(a[i]);
	for (int i = 1; i <= n; i ++) read(b[i]);

	int t = 0, sp = 0;
	for (int i = 1; i <= n; i ++)
		if (a[i] - b[i] >= 1) {
			pr[++ t] = par(a[i] - b[i], 1);
			pr[++ t] = par(a[i], -1);
		} else
			st[++ sp] = i;
	std::sort(pr + 1, pr + t + 1);

	for (int i = 1, j = 1, tot = 0; i <= sp; i ++) {
		while (j <= t and pr[j].first <= a[st[i]])
			tot += pr[j ++].second;
		suf[i] = tot ? 0 : 1;
	}
	for (int i = sp; i; i --) suf[i] += suf[i + 1];

	int ans = suf[1];
	for (int i = 1; i <= sp; i ++) {
		int A = a[st[i]], B = b[st[i]], d = B - A + 1;
		ans = std::min(ans, std::max(d, suf[i + 1]));
	}

	printf("%d\n", ans);
}
